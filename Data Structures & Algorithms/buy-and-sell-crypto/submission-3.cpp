// class Solution {
// public:
//     int maxProfit(vector<int>& prices) {
//         int buyPrice = prices[0];
//         int maxProfit = 0;
//         for (int price : prices) {  
//             int sellPrice =  price;       
//             maxProfit = max(maxProfit, sellPrice - buyPrice);
//             buyPrice = min(buyPrice, price);
//         }
//         return maxProfit;
//     }
// };




class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buyPrice = prices[0];
        int maxProfit = 0;
        for (int i=1; i < prices.size(); i++) {
            maxProfit = max(maxProfit, prices[i] - buyPrice);
            buyPrice = min(buyPrice, prices[i]);
        }
        return maxProfit;
    }
};








































