class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        
        vector<int> withoutLast(nums.begin(), nums.end() - 1);
        vector<int> withoutFirst(nums.begin() + 1, nums.end());
        return max(robLine(withoutLast), robLine(withoutFirst));
    }

private:
    int robLine(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        vector<int> dp(n);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for(int i=2; i<n; i++){
            int skipHouse = dp[i-1];
            int robHouse = nums[i] + dp[i-2]; 
            dp[i] = max(skipHouse, robHouse);
        }
        return dp[n-1];
    }

};