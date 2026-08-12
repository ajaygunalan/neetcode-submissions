class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxEnd = nums[0];
        int minEnd = nums[0];
        int ans = nums[0];

        for(int i=1; i<nums.size(); i++) {
            int x = nums[i];
            int oldMax = maxEnd;
            int oldMin = minEnd;

            maxEnd = max({x, x*oldMax, x*oldMin});
            minEnd = min({x, x*oldMax, x*oldMin});
            ans = max(ans, maxEnd);
        }
        return ans;
    }

};