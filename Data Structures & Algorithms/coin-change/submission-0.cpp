class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[x] = minimum coins needed to make x.
        // amount + 1 means x cannot be made yet.
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        
        for(int current=1; current<=amount; current++)
            for(int coin : coins)
                if(coin <= current)
                    dp[current] = min(dp[current], 1+dp[current-coin]);
        if(dp[amount] == amount + 1) return -1;
        return dp[amount];
    }
};
