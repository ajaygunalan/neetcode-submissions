#!/usr/bin/env python3
"""
NeetCode practice dashboard.

Reads the git history of this repo (which NeetCode's GitHub Sync writes to
automatically) and renders a single self-contained dashboard.html.

The atomic unit is a SOLVE: one *spaced* attempt at a problem. Submissions on
the same day collapse into one solve, and so does a redo the next day -- nothing
is recalled from memory that soon. Attempts MIN_GAP_DAYS or more apart count
separately. The goal is every problem solved REP_TARGET times.

Usage
-----
    python3 dashboard/dash.py                 # regenerate dashboard.html
    python3 dashboard/dash.py --open          # ...and open it
    python3 dashboard/dash.py --quiet         # no terminal summary
    python3 dashboard/dash.py --refresh-catalog   # re-pull NeetCode's problem list
    python3 dashboard/dash.py --date 2026-08-24   # preview a different day

Re-run it after a practice session. No server, no database.
"""

import argparse
import datetime as dt
import json
import os
import re
import subprocess
import sys
import webbrowser
from collections import defaultdict

# ---------------------------------------------------------------- config ----

REP_TARGET = 2                      # sittings per problem that counts as "done"
UNIVERSE = "nc250"                  # nc250 | nc150 | blind75
LADDER = [10, 30, 90]               # days until the next rep, by rep index
STRUGGLE_SUBS = 3                   # submissions in one session that means "shaky"
MIN_GAP_DAYS = 2                    # a redo sooner than this is the same solve, not a new one

# The weekly plan. New problems are blocked -- same pattern in a run, so you see
# what is alike. Weekend reps are interleaved -- pulled from older, different
# patterns, so you learn to tell them apart. Interleaving is the half that
# teaches pattern *recognition*: Taylor & Rohrer found it doubled next-day test
# scores by improving the ability to pair a problem with the right procedure.
WEEKDAY_NEW = 2                     # Mon-Fri: new problems per day
WEEKEND_REPS = 3                    # Sat/Sun: reps per day, mixed patterns
INTERLEAVE_DAYS = 10                # a pattern touched this recently is too fresh to rep
MILESTONES = ["2026-09-30", "2026-10-31", "2026-12-31"]

# Fraction of weeks actually practised -- allows roughly one week in six for
# travel, illness and holidays. Every projected date on the page scales with
# this, so it is the single biggest lever here: at 1.0 they read about a month
# early. Kept where the other tunables live rather than buried in the page.
LIVE_WEEKS = 0.82

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
CATALOG = os.path.join(HERE, "catalog.json")
OUT = os.path.join(HERE, "dashboard.html")
BUNDLE_HOST = "https://neetcode.io"

# ------------------------------------------------------------- catalogue ----


def refresh_catalog():
    """Re-extract NeetCode's problem list from their published JS bundle.

    The bundle carries `ncLink` (the slug this repo uses for folder names)
    alongside pattern, difficulty and the neetcode250/150/blind75 flags, so
    it is the only source that keys cleanly to our directories.
    """
    import urllib.request

    def get(url):
        req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
        return urllib.request.urlopen(req, timeout=60).read().decode("utf8", "replace")

    index = get(BUNDLE_HOST + "/")
    m = re.search(r'src="(main\.[0-9a-f]+\.js)"', index)
    if not m:
        sys.exit("could not find the main bundle on neetcode.io")
    js = get(f"{BUNDLE_HOST}/{m.group(1)}")

    # Each record starts with `{problem:"`. Slice from one start to the next so a
    # record missing `ncLink` can never borrow the following record's fields.
    starts = [m.start() for m in re.finditer(r'\{problem:"', js)]
    objs = [js[a:b] for a, b in zip(starts, starts[1:] + [len(js)])]

    field = lambda o, n: (re.search(n + r':"((?:[^"\\]|\\.)*)"', o) or [None, None])[1]
    flag = lambda o, n: bool(re.search(n + r":!0", o))

    seen = {}
    for o in objs:
        link = (field(o, "ncLink") or "").strip("/")
        if not link or link in seen:
            continue
        seen[link] = {
            "problem": field(o, "problem"),
            "pattern": field(o, "pattern"),
            "difficulty": field(o, "difficulty"),
            "lcLink": (field(o, "link") or "").strip("/"),
            "ncLink": link,
            "nc150": flag(o, "neetcode150"),
            "nc250": flag(o, "neetcode250"),
            "blind75": flag(o, "blind75"),
            "pro": flag(o, "pro"),
        }
    rows = list(seen.values())
    n250 = sum(r["nc250"] for r in rows)
    if n250 != 250:
        print(f"warning: extracted {n250} neetcode250 problems, expected 250", file=sys.stderr)
    with open(CATALOG, "w") as f:
        json.dump(rows, f, indent=0)
    print(f"catalog refreshed: {len(rows)} problems ({n250} in NC250) -> {CATALOG}")


def load_catalog():
    if not os.path.exists(CATALOG):
        sys.exit(f"missing {CATALOG}; run with --refresh-catalog")
    return {c["ncLink"]: c for c in json.load(open(CATALOG))}


# ------------------------------------------------------------- git parse ----


def collapse(days):
    """Merge sittings closer together than MIN_GAP_DAYS.

    A solve counts once per *spaced* attempt. Three submissions on one day is
    one solve; so is finishing on Monday and redoing it Tuesday -- nothing is
    recalled from memory a day later. Returns [(date, submissions), ...].
    """
    out = []
    for d in sorted(days):
        day = dt.date.fromisoformat(d)
        if out and (day - dt.date.fromisoformat(out[-1][0])).days < MIN_GAP_DAYS:
            out[-1][1] += days[d]          # same solve, just more submissions
        else:
            out.append([d, days[d]])
    return out


def read_sessions():
    """slug -> {date: submission_count}, from commit subjects."""
    log = subprocess.run(
        ["git", "-C", REPO, "log", "--pretty=%ad|%s", "--date=format:%Y-%m-%d"],
        capture_output=True, text=True, check=True,
    ).stdout.splitlines()

    sessions = defaultdict(lambda: defaultdict(int))
    for line in log:
        date, _, subject = line.partition("|")
        if not subject.startswith("Add: "):
            continue  # "Bulk sync" / "Initialize" carry no problem name
        slug = subject[5:].rsplit(" - submission-", 1)[0]
        sessions[slug][date] += 1
    return sessions


def due_date(dates, last_subs):
    """Next rep date under the expanding ladder, pulled back one rung if the
    most recent session needed a pile of submissions."""
    stage = min(len(dates) - 1, len(LADDER) - 1)
    if last_subs >= STRUGGLE_SUBS:
        stage = max(0, stage - 1)
    last = dt.date.fromisoformat(dates[-1])
    return (last + dt.timedelta(days=LADDER[stage])).isoformat()


# ----------------------------------------------------------------- build ----


def build(today):
    cat = load_catalog()
    sessions = read_sessions()

    unknown = sorted(s for s in sessions if s not in cat)
    if unknown:
        print(f"note: {len(unknown)} solved slug(s) not in catalog: {', '.join(unknown[:5])}",
              file=sys.stderr)

    universe = [c for c in cat.values() if c.get(UNIVERSE)]
    universe.sort(key=lambda c: (c["pattern"], c["problem"]))

    problems = []
    for c in universe:
        sittings = collapse(sessions.get(c["ncLink"], {}))
        dates = [d for d, _ in sittings]
        row = {
            "slug": c["ncLink"],
            "name": c["problem"],
            "pattern": c["pattern"],
            "diff": c["difficulty"][0],          # E / M / H
            "nc150": bool(c["nc150"]),
            "b75": bool(c["blind75"]),
            "s": sittings,                       # [[date, submissions], ...]
        }
        if dates:
            row["due"] = due_date(dates, sittings[-1][1])
        problems.append(row)

    return {
        "generated": today.isoformat(),
        "config": {
            "repTarget": REP_TARGET,
            "universeLabel": {"nc250": "NeetCode 250", "nc150": "NeetCode 150",
                              "blind75": "Blind 75"}[UNIVERSE],
            "weekdayNew": WEEKDAY_NEW,
            "weekendReps": WEEKEND_REPS,
            "interleaveDays": INTERLEAVE_DAYS,
            "liveWeeks": LIVE_WEEKS,
            "levelWords": [solve_label(k) for k in range(REP_TARGET + 1)],
            "milestones": MILESTONES,
        },
        "problems": problems,
    }


# ----------------------------------------------------------------- report ----


def ordinal(n):
    """1st, 2nd, 3rd, 4th ... 11th, 12th, 13th ... 21st, 22nd, 23rd."""
    if 11 <= n % 100 <= 13:
        return f"{n}th"
    return f"{n}{ {1: 'st', 2: 'nd', 3: 'rd'}.get(n % 10, 'th') }"


def fmt_long(d):
    """date(2026, 3, 23) -> '23rd March 2026'."""
    return f"{ordinal(d.day)} {d.strftime('%B')} {d.year}"


WORDS = ["Not started", "Solved once", "Solved twice"]


def solve_label(level):
    """0 -> 'Not started', 1 -> 'Solved once', 2 -> 'Solved twice', 3 -> ..."""
    return WORDS[level] if level < len(WORDS) else f"Solved {level} times"


def plan_for(day):
    """What the page will tell you to do on `day`, in words."""
    if day.weekday() >= 5:
        return f"{WEEKEND_REPS} reps, mixed patterns"
    return f"{WEEKDAY_NEW} new problems"


def terminal_report(data):
    """Echo the page's headline numbers. Which problems come up today is decided
    in the page itself, in one place, so this deliberately does not repeat it."""
    P = data["problems"]
    today = dt.date.fromisoformat(data["generated"])
    solved = [p for p in P if p["s"]]
    at = lambda n: sum(1 for p in P if len(p["s"]) >= n)
    pc = lambda n: f"{round(100 * n / len(P))}%"
    bold = lambda t: f"\033[1m{t}\033[0m" if sys.stdout.isatty() else t

    due = sum(1 for p in solved if dt.date.fromisoformat(p["due"]) <= today)

    print()
    print(bold(f"  {data['config']['universeLabel']} · {fmt_long(today)}"))
    for level in range(REP_TARGET, -1, -1):
        # the top bucket is "REP_TARGET or more", matching how the page caps it
        n = (len(P) - at(1) if level == 0
             else at(level) if level == REP_TARGET
             else at(level) - at(level + 1))
        print(f"    {solve_label(level):<16}{pc(n):>5}{n:>6}")
    print()
    print(f"  today: {plan_for(today)}")
    print(f"  {due} problems are due for another solve")
    print()


# ------------------------------------------------------------------- html ----

TEMPLATE = r"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Today</title>
<style>
:root{
  color-scheme:light;
  --bg:#f9f9f7; --card:#fcfcfb; --ink:#0b0b0b; --ink2:#52514e; --muted:#898781;
  --line:#e1e0d9; --hair:rgba(11,11,11,.09); --accent:#2a78d6;
  --r0:#e6e5df; --r1:#86b6ef; --r2:#3987e5; --r3:#1c5cab;
}
@media (prefers-color-scheme:dark){:root:not([data-theme="light"]){
  color-scheme:dark;
  --bg:#0d0d0d; --card:#1a1a19; --ink:#fff; --ink2:#c3c2b7; --muted:#898781;
  --line:#2c2c2a; --hair:rgba(255,255,255,.10); --accent:#3987e5;
  --r0:#2c2c2a; --r1:#184f95; --r2:#2a78d6; --r3:#6da7ec;
}}
:root[data-theme="dark"]{
  color-scheme:dark;
  --bg:#0d0d0d; --card:#1a1a19; --ink:#fff; --ink2:#c3c2b7; --muted:#898781;
  --line:#2c2c2a; --hair:rgba(255,255,255,.10); --accent:#3987e5;
  --r0:#2c2c2a; --r1:#184f95; --r2:#2a78d6; --r3:#6da7ec;
}
*{box-sizing:border-box}
body{
  margin:0;background:var(--bg);color:var(--ink);
  font:15px/1.5 system-ui,-apple-system,"Segoe UI",sans-serif;
  -webkit-font-smoothing:antialiased;
  display:flex;align-items:flex-start;justify-content:center;padding:56px 20px 0;
}
main{width:100%;max-width:600px}
main::after{content:"";display:block;height:9vh}    /* room to scroll past the end */

.kicker{
  font-size:11.5px;font-weight:600;letter-spacing:.11em;text-transform:uppercase;
  color:var(--muted);margin-bottom:10px;
}
h1{font-size:31px;font-weight:600;letter-spacing:-.025em;margin:0 0 5px;line-height:1.15}
.date{color:var(--ink2);font-size:14.5px;margin-bottom:6px}
.sub{color:var(--ink2);font-size:13.5px;margin:0 0 13px}

ol{list-style:none;margin:0;padding:0;
   background:var(--card);border:1px solid var(--hair);border-radius:12px;overflow:hidden}
li{display:flex;align-items:baseline;gap:14px;padding:16px 20px;border-bottom:1px solid var(--line)}
li:last-child{border-bottom:0}
.n{color:var(--muted);font-size:12px;font-variant-numeric:tabular-nums;
   min-width:14px;flex:none;padding-top:2px}
.body{flex:1;min-width:0}
.title{font-size:17px;font-weight:500;letter-spacing:-.01em;line-height:1.35}
a.title{color:inherit;text-decoration:none}
a.title:hover{color:var(--accent)}
.meta{color:var(--muted);font-size:12.5px;margin-top:3px}
.meta b{font-weight:500;color:var(--ink2)}

.empty{padding:26px 20px;color:var(--ink2);font-size:15px;text-align:center}
.empty .big{font-size:19px;color:var(--ink);font-weight:500;margin-bottom:5px}

.blk{margin-top:32px}
.blk .kicker{margin-bottom:11px}
table{border-collapse:collapse;width:100%;font-size:13px}
th{text-align:right;font-weight:500;color:var(--muted);font-size:11.5px;
   padding:0 0 7px 12px;white-space:nowrap}
th.l{text-align:left;padding-left:0}
td{text-align:right;padding:7px 0 7px 12px;font-variant-numeric:tabular-nums;
   color:var(--ink);border-top:1px solid var(--line)}
td.l{text-align:left;color:var(--ink2);padding-left:0}
tr.plan td{color:var(--ink)} tr.plan td.l{color:var(--ink);font-weight:600}
tr.mine td{color:var(--ink2)}
.blk h3{font-size:12px;font-weight:600;color:var(--ink2);margin:26px 0 10px;letter-spacing:0}
.legend{display:flex;gap:16px;flex-wrap:wrap;align-items:center;
        color:var(--ink2);font-size:11.5px;margin-bottom:6px}
.legend span{display:inline-flex;align-items:center;gap:6px}
.legend i{width:14px;height:2px;border-radius:1px;flex:none}
.chartwrap{overflow-x:auto}
#chart{display:block;width:100%;overflow:visible}
.gl{stroke:var(--line);stroke-width:1}
.tk{fill:var(--muted);font-size:10.5px;font-variant-numeric:tabular-nums}
.dl{font-size:11px;font-weight:600;font-variant-numeric:tabular-nums}
#tip{position:fixed;pointer-events:none;opacity:0;transition:opacity .08s;z-index:9;
     background:var(--card);border:1px solid var(--hair);border-radius:7px;
     padding:7px 10px;font-size:11.5px;color:var(--ink2);
     box-shadow:0 4px 14px rgba(0,0,0,.14);white-space:nowrap}
#tip b{color:var(--ink);display:block;margin-bottom:3px;font-weight:600}
.bar{height:6px;border-radius:3px;background:var(--r0);overflow:hidden;
     display:flex;gap:2px;margin-bottom:15px}
.bar i{display:block;height:100%}
dl{margin:0;display:grid;grid-template-columns:11px 1fr auto auto;gap:8px 11px;align-items:center}
dl .sw{width:11px;height:11px;border-radius:3px;box-shadow:inset 0 0 0 1px var(--hair)}
dl dt{color:var(--ink2);font-size:13.5px}
dl dd{margin:0;text-align:right;font-size:13.5px;font-variant-numeric:tabular-nums;color:var(--ink)}
dl dd.pc{font-weight:600;min-width:42px}
dl dd.ct{color:var(--muted);min-width:34px;font-size:12.5px}

.cats{display:grid;grid-template-columns:1fr;gap:9px}
.cat{display:grid;grid-template-columns:1fr 78px 40px;gap:11px;align-items:center}
.cat .nm{font-size:13px;color:var(--ink2);white-space:nowrap;overflow:hidden;text-overflow:ellipsis}
.cat.here .nm{color:var(--ink);font-weight:600}
.cat .mini{height:6px;border-radius:3px;background:var(--r0);display:flex;gap:1.5px;overflow:hidden}
.cat .mini i{display:block;height:100%}
.cat .pc{font-size:12px;text-align:right;font-variant-numeric:tabular-nums;color:var(--muted)}
.cat.here .pc{color:var(--ink2)}

</style>
</head>
<body>
<main>
  <h1 id="head"></h1>
  <div class="date" id="date"></div>

  <section class="blk">
    <div class="kicker">Today</div>
    <div class="sub" id="sub"></div>
    <ol id="list"></ol>
  </section>

  <section class="blk">
    <div class="kicker">Progress</div>
    <div class="bar" id="bar"></div>
    <dl id="break"></dl>
  </section>

  <section class="blk">
    <div class="kicker">Pace</div>
    <table id="pace"></table>
    <h3>Where this gets you</h3>
    <div class="legend" id="leg"></div>
    <div class="chartwrap"><svg id="chart" role="img"
         aria-label="Projected problems solved once and twice over time"></svg></div>
    <table id="fin"></table>
  </section>

  <section class="blk">
    <div class="kicker">By category</div>
    <div class="cats" id="cats"></div>
  </section>
</main>
<div id="tip" role="tooltip"></div>
<script id="data" type="application/json">/*__DATA__*/</script>
<script>
const DATA=JSON.parse(document.getElementById('data').textContent);
const CFG=DATA.config, P=DATA.problems, REP_TARGET=CFG.repTarget, N=P.length;
function iso2d(s){const[a,b,c]=s.split('-').map(Number);return new Date(Date.UTC(a,b-1,c));}
const TODAY=iso2d(DATA.generated);
const addDays=(d,n)=>new Date(d.getTime()+n*864e5);
const dayDiff=(a,b)=>Math.round((a-b)/864e5);
function ord(n){const t=n%100;return n+(t>=11&&t<=13?'th':n%10===1?'st':n%10===2?'nd':n%10===3?'rd':'th');}
const mon=(d,l)=>d.toLocaleDateString('en-GB',{month:l?'long':'short',timeZone:'UTC'});
const fmtLong=d=>`${ord(d.getUTCDate())} ${mon(d,1)} ${d.getUTCFullYear()}`;
const fmtShort=d=>`${ord(d.getUTCDate())} ${mon(d)}`;
const DIFF={E:'Easy',M:'Medium',H:'Hard'};

const solved=P.filter(p=>p.s.length);
const START=(()=>{let m=null;for(const p of solved){const d=iso2d(p.s[0][0]);if(!m||d<m)m=d;}
  return m||TODAY;})();
const atLeast=n=>P.filter(p=>p.s.length>=n).length;
const lastOf=p=>p.s[p.s.length-1][0];
const flat=[];
for(const p of solved) p.s.forEach(([d,n],i)=>flat.push({d,rep:i+1,p}));
flat.sort((a,b)=>a.d<b.d?-1:1);

const isWeekend=d=>[0,6].includes(d.getUTCDay());
const belowTarget=p=>+(p.s.length>=REP_TARGET);
const queue=solved.map(p=>({p,over:dayDiff(TODAY,iso2d(p.due))}))
  .filter(q=>q.over>=0)
  .sort((a,b)=>belowTarget(a.p)-belowTarget(b.p)||(b.over-a.over)||(a.p.s.length-b.p.s.length));

const fresh=new Set(flat.filter(f=>dayDiff(TODAY,iso2d(f.d))<=CFG.interleaveDays).map(f=>f.p.pattern));
// Best first: a pattern gone cold and not already picked today. Then any unused
// pattern, then whatever is left -- so the reps span as many patterns as possible.
function pickReps(n){
  const out=[],used=new Set(),taken=new Set();
  const add=q=>{out.push(q);used.add(q.p.pattern);taken.add(q.p.slug);};
  const passes=[q=>!fresh.has(q.p.pattern)&&!used.has(q.p.pattern),
                q=>!taken.has(q.p.slug)&&!used.has(q.p.pattern),
                q=>!taken.has(q.p.slug)];
  for(const ok of passes)
    for(const q of queue){ if(out.length>=n) return out; if(ok(q)) add(q); }
  return out;
}
// how much of each pattern is started -- one pass, not one per comparison
const patTotal={}, patStarted={};
for(const p of P){
  patTotal[p.pattern]=(patTotal[p.pattern]||0)+1;
  if(p.s.length) patStarted[p.pattern]=(patStarted[p.pattern]||0)+1;
}
const coverage=k=>(patStarted[k]||0)/patTotal[k];

function pickNew(n){
  const unseen=P.filter(p=>!p.s.length);
  if(!unseen.length)return[];
  const lastNew=[...flat].reverse().find(f=>f.rep===1);
  // stay in the pattern you were last working; otherwise start the weakest one
  const block=lastNew&&unseen.some(p=>p.pattern===lastNew.p.pattern)
    ? lastNew.p.pattern
    : [...new Set(unseen.map(p=>p.pattern))]
        .reduce((a,b)=>coverage(b)<coverage(a)?b:a);
  const rank={E:0,M:1,H:2};
  return unseen.filter(p=>p.pattern===block)
    .sort((a,b)=>rank[a.diff]-rank[b.diff]||(b.b75?1:0)-(a.b75?1:0)||(b.nc150?1:0)-(a.nc150?1:0))
    .slice(0,n);
}

const NS='http://www.w3.org/2000/svg';
const make=ns=>(t,a={},...k)=>{
  const n=ns?document.createElementNS(ns,t):document.createElement(t);
  for(const[q,v]of Object.entries(a))n.setAttribute(q,v);
  for(const c of k.flat())if(c!=null)n.append(c.nodeType?c:document.createTextNode(c));
  return n;};
const el=make(null), sv=make(NS);

const weekend=isWeekend(TODAY);
const dayName=TODAY.toLocaleDateString('en-GB',{weekday:'long',timeZone:'UTC'});
const items = weekend ? pickReps(CFG.weekendReps) : pickNew(CFG.weekdayNew);

document.getElementById('head').textContent=CFG.universeLabel;
document.getElementById('date').textContent=`${dayName}, ${fmtLong(TODAY)}`;
document.getElementById('sub').textContent =
  weekend ? `${items.length} rep${items.length===1?'':'s'}, mixed patterns`
          : (items.length ? `${items.length} new problem${items.length===1?'':'s'} · ${items[0].pattern}`
                          : 'nothing new left to start');

const list=document.getElementById('list');
if(!items.length){
  list.append(el('div',{class:'empty'},
    el('div',{class:'big'},weekend?'Nothing due today':`All ${N} started`),
    weekend?'Next reps fall due soon — enjoy it.':'Weekends are for reps from here.'));
} else {
  items.forEach((it,i)=>{
    const p = weekend ? it.p : it;
    const meta = weekend
      ? el('div',{class:'meta'}, `${p.pattern} · ${DIFF[p.diff]} · last done `,
          el('b',{},fmtShort(iso2d(lastOf(p)))), it.over>0?` · ${it.over} days overdue`:'')
      : el('div',{class:'meta'}, `${p.pattern} · ${DIFF[p.diff]}`,
          p.b75?' · Blind 75':p.nc150?' · NeetCode 150':'');
    list.append(el('li',{},
      el('div',{class:'n'},String(i+1)),
      el('div',{class:'body'},
        el('a',{class:'title',href:`https://neetcode.io/problems/${p.slug}`,target:'_blank'},p.name),
        meta)));
  });
}

const pcs = n => Math.round(100*n/N) + '%';
const lvOf = p => Math.min(p.s.length, REP_TARGET);   // capped: at target it is done
const LEVELS = [...Array(REP_TARGET+1).keys()];       // 0 .. REP_TARGET

// One stacked bar, deepest level first, widths as a share of `total`.
// Level 0 is left to the track's own --r0 background rather than drawn.
function stack(box, counts, total){
  for(let lvl=REP_TARGET; lvl>=1; lvl--){
    if(!counts[lvl]) continue;
    const i=el('i');
    i.style.width=(100*counts[lvl]/total)+'%';
    i.style.background=`var(--r${lvl})`;
    box.append(i);
  }
  return box;
}

/* progress: every problem in the set, by how many separate days you have solved it */
{
  const lv=LEVELS.map(k=>P.filter(p=>lvOf(p)===k).length);
  stack(document.getElementById('bar'), lv, N);
  const dl=document.getElementById('break');
  for(let lvl=REP_TARGET; lvl>=0; lvl--){
    const sw=el('div',{class:'sw'}); sw.style.background=`var(--r${lvl})`;
    dl.append(sw, el('dt',{},CFG.levelWords[lvl]),
              el('dd',{class:'pc'},pcs(lv[lvl])), el('dd',{class:'ct'},String(lv[lvl])));
  }
}

/* every category, shaded the same way */
{
  const pats={};
  for(const p of P) (pats[p.pattern] ||= []).push(p);
  const box=document.getElementById('cats');
  const here = (!weekend && items.length) ? items[0].pattern : null;
  const score={};
  for(const k in pats)
    score[k]=pats[k].reduce((t,p)=>t+lvOf(p),0)/(pats[k].length*REP_TARGET);
  Object.keys(pats)
    .sort((a,b)=>score[b]-score[a] || a.localeCompare(b))
    .forEach(k=>{
      const l=pats[k], started=l.filter(p=>p.s.length).length;
      const counts=LEVELS.map(k=>l.filter(p=>lvOf(p)===k).length);
      const mini=stack(el('div',{class:'mini'}), counts, l.length);
      box.append(el('div',{class:'cat'+(k===here?' here':''),
                           title:`${started} of ${l.length} started`},
        el('div',{class:'nm'},k), mini,
        el('div',{class:'pc'},`${started}/${l.length}`)));
    });
}

/* pace: the plan vs what you have actually been doing */
{
  const LIVE=CFG.liveWeeks;           // fraction of weeks actually practised
  const once0=atLeast(1), twice0=atLeast(REP_TARGET);

  // measured across the whole history, first solve to today
  const span=dayDiff(TODAY,START)+1;
  let nwd=0,nwe=0;
  for(let i=0;i<span;i++) isWeekend(addDays(START,i))?nwe++:nwd++;
  const onWeekend=f=>isWeekend(iso2d(f.d));
  const wdRate=flat.filter(f=>!onWeekend(f)).length/nwd;
  const weRate=flat.filter(f=>onWeekend(f)).length/nwe;

  // Walk forward a week at a time. Weekday slots take new problems until none
  // are left, then spill into reps; weekend slots are always reps.
  function walk(newPerWeek, repPerWeek, weeks){
    let unseen=N-once0, owed=once0-twice0, done2=twice0, seen=once0;
    const out=[{w:0,seen,done2}];
    for(let w=1; w<=weeks; w++){
      const nw=Math.min(unseen, newPerWeek*LIVE);
      unseen-=nw; seen+=nw; owed+=nw;
      const spare=newPerWeek*LIVE-nw;
      const rp=Math.min(owed, repPerWeek*LIVE+spare);
      owed-=rp; done2+=rp;
      out.push({w,seen,done2});
    }
    return out;
  }
  const project=(nw,rp,weeks)=>{const t=walk(nw,rp,Math.max(1,Math.ceil(weeks)));
    const r=t[Math.min(t.length-1,Math.round(weeks))];
    return {seen:Math.round(r.seen), done2:Math.round(r.done2)};};
  // when every problem has reached the target, at this pace
  function finish(newPerWeek, repPerWeek){
    for(const r of walk(newPerWeek,repPerWeek,520))
      if(r.done2>=N-0.5) return addDays(TODAY,r.w*7);
    return null;
  }
  const PLAN=[5*CFG.weekdayNew, 2*CFG.weekendReps];
  const MINE=[5*wdRate, 2*weRate];

  const row=(cls,cells)=>'<tr class="'+cls+'">'+cells.map((c,i)=>
      `<td class="${i?'':'l'}">${c}</td>`).join('')+'</tr>';

  document.getElementById('pace').innerHTML =
    '<tr><th class="l"></th><th>weekday</th><th>weekend day</th><th>per week</th></tr>'
    + row('plan',['Your plan', CFG.weekdayNew.toFixed(1), CFG.weekendReps.toFixed(1),
                  (PLAN[0]+PLAN[1]).toFixed(0)])
    + row('mine',['Your pace so far', wdRate.toFixed(1), weRate.toFixed(1),
                  (MINE[0]+MINE[1]).toFixed(1)]);

  /* ---- the chart ---- */
  // `walk` tracks two lines only: started, and reached the target. That is the
  // whole model, so a REP_TARGET above 2 would need levels in between.
  const SERIES=[['seen','var(--r1)',CFG.levelWords[1].replace(/^Solved /,'')],
                ['done2','var(--r2)',CFG.levelWords[REP_TARGET].replace(/^Solved /,'')]];
  const marks=CFG.milestones.map(iso2d).filter(d=>dayDiff(d,TODAY)>0);
  const shown=marks.slice(-2);              // the milestones the table also lists
  const endD=(()=>{let m=TODAY;for(const r of [PLAN,MINE]){const d=finish(r[0],r[1]);
    if(d&&d>m)m=d;} return addDays(m,10);})();
  const WK=Math.ceil(dayDiff(endD,TODAY)/7);
  const trPlan=walk(PLAN[0],PLAN[1],WK), trMine=walk(MINE[0],MINE[1],WK);

  const W=620,H=250,M={t:18,r:128,b:30,l:32};
  const X=d=>M.l+(W-M.l-M.r)*dayDiff(d,TODAY)/dayDiff(endD,TODAY);
  const Xw=w=>X(addDays(TODAY,w*7));
  const Y=v=>M.t+(H-M.t-M.b)*(1-v/N);
  const g=document.getElementById('chart');
  g.setAttribute('viewBox',`0 0 ${W} ${H}`);

  const step=Math.max(10, Math.round(N/5/10)*10);
  for(let v=0;v<=N;v+=step){
    g.append(sv('line',{class:'gl',x1:M.l,x2:W-M.r,y1:Y(v),y2:Y(v)}),
             sv('text',{class:'tk',x:M.l-7,y:Y(v)+3.5,'text-anchor':'end'},String(v)));
  }
  for(const d of marks){
    if(d>endD) continue;
    g.append(sv('line',{class:'gl',x1:X(d),x2:X(d),y1:M.t,y2:Y(0)}),
             sv('text',{class:'tk',x:X(d),y:H-M.b+15,'text-anchor':'middle'},
                `${fmtShort(d)} ${String(d.getUTCFullYear()).slice(2)}`));
  }
  g.append(sv('text',{class:'tk',x:M.l,y:H-M.b+15,'text-anchor':'middle'},'today'));

  const path=(tr,key)=>tr.map((r,i)=>(i?'L':'M')+Xw(r.w).toFixed(1)+' '+Y(r[key]).toFixed(1)).join(' ');
  for(const [key,col] of SERIES){
    g.append(sv('path',{d:path(trMine,key),fill:'none',stroke:col,'stroke-width':2,
      'stroke-dasharray':'2 4','stroke-linecap':'round',opacity:.8}));
    g.append(sv('path',{d:path(trPlan,key),fill:'none',stroke:col,'stroke-width':2,
      'stroke-linejoin':'round','stroke-linecap':'round'}));
  }
  // where each plan line reaches the full set — labels live in the right margin,
  // stacked, so they can never collide with the curves or with each other
  SERIES.forEach(([key,col,lab],i)=>{
    const dy=i?13:-7;
    const hit=trPlan.find(r=>r[key]>=N-0.5);
    if(!hit) return;
    g.append(sv('circle',{cx:Xw(hit.w),cy:Y(N),r:4,fill:col,
                          stroke:'var(--card)','stroke-width':2}));
    g.append(sv('text',{class:'dl',x:W-M.r+11,y:Y(N)+dy,fill:col},
      `${N} ${lab} · ${fmtShort(addDays(TODAY,hit.w*7))}`));
  });
  // quiet dots where the milestones cross; the table below carries the numbers
  for(const d of shown){
    if(d>endD) continue;
    const w=Math.min(Math.round(dayDiff(d,TODAY)/7),trPlan.length-1), r=trPlan[w];
    for(const [key,col] of SERIES)
      g.append(sv('circle',{cx:X(d),cy:Y(r[key]),r:3.5,fill:col,
                            stroke:'var(--card)','stroke-width':2}));
  }

  document.getElementById('leg').innerHTML =
      SERIES.map(([,col,lab])=>`<span><i style="background:${col}"></i>solved ${lab}</span>`).join('')
    + `<span><i style="background:none;height:0;width:18px;`
    + `border-top:2px solid var(--muted)"></i>your plan</span>`
    + `<span><i style="background:none;height:0;width:18px;`
    + `border-top:2px dotted var(--muted)"></i>your pace so far</span>`;

  /* hover: read any week off the chart */
  const tip=document.getElementById('tip');
  const hit=sv('rect',{x:M.l,y:M.t,width:W-M.l-M.r,height:H-M.t-M.b,fill:'transparent'});
  g.append(hit);
  hit.addEventListener('mousemove',e=>{
    const bb=g.getBoundingClientRect();
    const px=(e.clientX-bb.left)/bb.width*W;
    const w=Math.max(0,Math.min(WK,Math.round((px-M.l)/((W-M.l-M.r)/WK))));
    const a=trPlan[w], b=trMine[Math.min(w,trMine.length-1)];
    tip.innerHTML=`<b>${fmtLong(addDays(TODAY,w*7))}</b>`
      + `plan &nbsp;${SERIES.map(([k,,lab])=>`${Math.round(a[k])} ${lab}`).join(' · ')}<br>`
      + `yours ${SERIES.map(([k,,lab])=>`${Math.round(b[k])} ${lab}`).join(' · ')}`;
    tip.style.opacity=1;
    const r=tip.getBoundingClientRect();
    tip.style.left=Math.min(e.clientX+14,innerWidth-r.width-8)+'px';
    tip.style.top=(e.clientY-r.height-12)+'px';
  });
  hit.addEventListener('mouseleave',()=>tip.style.opacity=0);

  const fin=rate=>{const d=finish(rate[0],rate[1]);return d?fmtLong(d):'—';};
  const at=(rate,d)=>{const r=project(rate[0],rate[1],dayDiff(d,TODAY)/7);
    return `${r.seen} / ${r.done2}`;};
  document.getElementById('fin').innerHTML =
    '<tr><th class="l"></th>'
    + shown.map(d=>`<th>${fmtShort(d)} ${d.getUTCFullYear()}</th>`).join('')
    + `<th>all ${N} ${SERIES[1][2]}</th></tr>`
    + row('plan',['Your plan', ...shown.map(d=>at(PLAN,d)), fin(PLAN)])
    + row('mine',['Your pace so far', ...shown.map(d=>at(MINE,d)), fin(MINE)]);

}
</script>
</body>
</html>
"""


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--refresh-catalog", action="store_true",
                    help="re-pull NeetCode's problem list before building")
    ap.add_argument("--open", action="store_true", help="open the dashboard when done")
    ap.add_argument("--quiet", action="store_true", help="skip the terminal summary")
    ap.add_argument("--date", metavar="YYYY-MM-DD",
                    help="pretend it is this day (previews a weekday vs weekend plan)")
    args = ap.parse_args()

    if args.refresh_catalog:
        refresh_catalog()

    today = dt.date.fromisoformat(args.date) if args.date else dt.date.today()
    if args.date:
        print(f"  previewing as {fmt_long(today)} "
              f"({'weekend' if today.weekday() >= 5 else 'weekday'})")
    data = build(today)
    blob = json.dumps(data, separators=(",", ":"))
    html = TEMPLATE.replace("/*__DATA__*/", blob)
    with open(OUT, "w") as f:
        f.write(html)

    if not args.quiet:
        terminal_report(data)
    print(f"  wrote {OUT}  ({len(html)//1024} KB)\n")

    if args.open:
        webbrowser.open("file://" + OUT)


if __name__ == "__main__":
    main()
