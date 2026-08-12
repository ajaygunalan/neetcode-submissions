class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1,0);

        dp[0] = 1;
        dp[1] = s[0] == '0' ? 0 : 1;

        for(int i=2; i<=n; i++) {
            //one digit
            int oneDigit = s[i-1] - '0';
            if(oneDigit >= 1) dp[i] += dp[i-1];

            //two digit
            int twoDigit = (s[i-2] - '0')*10 + oneDigit;
            if(twoDigit >= 10 && twoDigit <= 26) dp[i] += dp[i-2];
        }
        return dp[n];
    }
};
