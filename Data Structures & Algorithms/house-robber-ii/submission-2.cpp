class Solution {
private:
    int rob_linear(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        if(n == 1) return dp[0];

        dp[1] = max(nums[1], dp[0]);
        for(int i=2; i<n; i++) {
            int robHouse = nums[i] +  dp[i-2];
            int skipHouse = dp[i-1];
            dp[i] = max(skipHouse, robHouse);
        }
        return dp[n-1];
    }
public:
int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        std::vector<int> skipFirstHouse(nums.begin()+1, nums.end());
        std::vector<int> skipLastHouse(nums.begin(), nums.end()-1);
        return max(rob_linear(skipFirstHouse), rob_linear(skipLastHouse));
    }

};
