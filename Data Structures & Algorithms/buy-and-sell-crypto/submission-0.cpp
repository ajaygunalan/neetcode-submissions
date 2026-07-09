class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buyPrice = prices[0];
        int maxProfit = 0;
        for (int price : prices) {            
            maxProfit = max(maxProfit, price - buyPrice);
            buyPrice = min(buyPrice, price);
        }
        return maxProfit;
    }
};
