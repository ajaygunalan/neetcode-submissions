class Solution {
private:
    string s;
    vector<vector<bool>> dp;

    bool isPalindrome(int l, int r) {
        if(s[l] != s[r]) return false;
        int currentLen =  r-l+1;
        if(currentLen <= 3) return true;
        return dp[l+1][r-1];
    }
public:
    string longestPalindrome(string s) {
        this->s =  std::move(s);
        int n = this->s.size();
        dp.assign(n, vector<bool>(n, false));
        int bestStart = 0, bestLen = 0;

        for(int l=n-1; l>=0; l--) {
            for(int r=l; r<n; r++) {
                dp[l][r] = isPalindrome(l, r);
                if(dp[l][r]) {
                    int currentLen = r-l+1;
                    if(currentLen > bestLen) {
                        bestStart = l;
                        bestLen =  currentLen;
                    }
                }
            }
        }
        return this->s.substr(bestStart, bestLen);
    }
};