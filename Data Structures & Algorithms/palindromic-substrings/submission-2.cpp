class Solution {
private:
    string s;
    vector<vector<char>> dp;

    bool isPalindrome(int i, int j) {
        if(s[i] != s[j]) return false;
        if(j-i+1 <= 3) return true;
        return dp[i+1][j-1];
    }

public:
    int countSubstrings(string s) {
        this->s = std::move(s);
        int n = this->s.size();
        dp.assign(n, vector<char>(n, 0));
        int count = 0;

        for(int i=n-1; i>=0; i--) {
            for(int j=i; j<n; j++) {
                dp[i][j] = isPalindrome(i, j);
                if(dp[i][j]) count++;
            }
        }
        return count;
    }
};
