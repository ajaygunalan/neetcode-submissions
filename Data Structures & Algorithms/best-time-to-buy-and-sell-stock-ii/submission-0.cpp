class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> dailyProfit(prices.size(), 0);
        for(int i=1; i<prices.size(); i++) 
            dailyProfit[i] = max(0, prices[i] - prices[i-1]);
        return ranges::fold_left(dailyProfit, 0, plus{});
    }

    // int maxProfit(vector<int>& prices) {
    //     int profit=0;
    //     for(int i=0; i<prices.size(), i++)
    //         profit += max(0, prices[i] - prices[i-1]);
    //     return profit;
    // }
};