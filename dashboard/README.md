# Practice dashboard

A single self-contained `dashboard.html`, generated from this repo's git history.

```bash
python3 dashboard/dash.py --open              # regenerate and open
python3 dashboard/dash.py                     # regenerate only
python3 dashboard/dash.py --quiet             # no terminal summary
python3 dashboard/dash.py --date 2026-08-24   # preview another day
```

Run it after a practice session. NeetCode's [GitHub Sync](https://neetcode.io/profile/github)
commits each submission here automatically, so the git log *is* the dataset —
there is nothing to log by hand, no server and no database.

## How a "solve" is counted

This is the rule everything else depends on.

| | |
|---|---|
| **Solve** | one *spaced* attempt at a problem — the unit that counts |
| **Submissions** | how many tries inside one attempt; a struggle signal, not progress |

Two rules collapse raw submissions into solves:

1. **Same day = one solve.** Three submissions on Tuesday is one solve, not three.
2. **Next day = still the same solve.** Finishing Monday and redoing it Tuesday is
   one solve. Nothing is recalled *from memory* a day later, so it teaches almost
   nothing. A gap of `MIN_GAP_DAYS` (default 2) or more is what makes it count again.

So "solved twice" means two attempts genuinely separated in time, not two
submissions. The goal is every problem in `UNIVERSE` solved `REP_TARGET` times.

## Config

Constants at the top of `dash.py`:

| | default | |
|---|---|---|
| `REP_TARGET` | `2` | spaced solves per problem that counts as done |
| `UNIVERSE` | `"nc250"` | also accepts `"nc150"` or `"blind75"` |
| `MIN_GAP_DAYS` | `2` | a redo sooner than this is the same solve |
| `LADDER` | `[10, 30, 90]` | days until the next solve is due |
| `WEEKDAY_NEW` | `2` | Mon–Fri: new problems per day, one pattern at a time |
| `WEEKEND_REPS` | `3` | Sat/Sun: reps per day, deliberately mixed patterns |
| `INTERLEAVE_DAYS` | `10` | a pattern touched this recently is too fresh to rep |
| `STRUGGLE_SUBS` | `3` | submissions in one solve that pulls the next one in a rung |
| `MILESTONES` | Sep/Oct/Dec 30–31 | checkpoints on the projection chart; the last two also get a table column |
| `LIVE_WEEKS` | `0.82` | fraction of weeks actually practised — scales every projected date |

**Two things are hardcoded that the table might imply are not.** `WEEKDAY_NEW`
and `WEEKEND_REPS` name *how many*, but not *which days*: Monday–Friday and
Saturday/Sunday are baked into both the page and the summary. And the projection
models exactly two lines — started, and reached the target — so `REP_TARGET`
above 2 would need levels in between before the chart meant anything.

## catalog.json

Problem metadata — pattern, difficulty, and the NeetCode 250 / 150 / Blind 75
flags — keyed by the same slug this repo uses for folder names. Extracted from
NeetCode's published JS bundle, which is the only source that carries that slug
(`ncLink`) alongside the flags.

```bash
python3 dashboard/dash.py --refresh-catalog
```

Worth re-running if NeetCode changes the 250, or if `dash.py` warns that a
solved folder has no catalog entry. It prints the total and the NC250 count,
and warns if the latter is not 250.

## What the page shows

Top to bottom: today's work (new problems on a weekday, reps on a weekend), the
progress breakdown, a pace section comparing your plan against what you have
actually averaged since the first solve — with a chart projecting both forward
to the milestone dates — and finally per-category coverage.

Which problems come up today is decided in the page, in one place. The terminal
summary deliberately does not repeat that logic, so the two cannot drift.

## Note

These files live inside a repo that NeetCode writes to automatically. Sync only
adds solution files under `Data Structures & Algorithms/`, so `dashboard/` is
left alone — but that is a property of how sync behaves today, not a guarantee.
