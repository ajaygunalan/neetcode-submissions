class Solution {
private:
    string s;
    vector<vector<char>> dp;

    bool isPalindrome(int i, int j) {
        if (s[i] != s[j]) return false;
        int currentLen = j - i + 1;
        if (currentLen <= 3) return true;
        return dp[i + 1][j - 1];
    }

public:
    string longestPalindrome(string s) {
        this->s = std::move(s);
        int n = this->s.size();
        dp.assign(n, vector<char>(n, 0));

        int bestStart = 0, bestLen = 0;

        // i DESCENDS so that row i+1 is already complete before
        // isPalindrome reads dp[i+1][j-1]. Reverse this loop and every
        // palindrome of length 4+ is silently rejected.
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                dp[i][j] = isPalindrome(i, j);
                if (dp[i][j]) {
                    int currentLen = j - i + 1;
                    if (currentLen > bestLen) {
                        bestStart = i;
                        bestLen = currentLen;
                    }
                }
            }
        }
        return this->s.substr(bestStart, bestLen);
    }
};