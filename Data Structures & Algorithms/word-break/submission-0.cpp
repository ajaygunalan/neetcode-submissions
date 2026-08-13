class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string_view> dict(wordDict.begin(), wordDict.end());
        int maxWordLen = ranges::max(wordDict, {}, [](const string& w) { return w.size(); }).size();
        int n = s.size();
        string_view sv = s;
        vector<bool> dp(n + 1);
        dp[0] = true;
        for (int end = 1; end <= n; end++)
            for (int start = end - 1; start >= 0 && end - start <= maxWordLen; start--)
                if (dp[start] && dict.contains(sv.substr(start, end - start))) {
                    dp[end] = true;
                    break;
                }
        return dp[n];
    }
};