class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        ranges::sort(nums);
        vector<vector<int>> result;
        int n = nums.size();
        for(int i=0; i<n; i++) {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            for(int j=i+1; j<n; j++) {
                if(j > i+1 && nums[j] == nums[j-1]) continue;
                int l = j+1, r=n-1;
                while(l < r) {
                    long long sum  = (long long)nums[i] + nums[j] + nums[l] + nums[r];
                    if(sum < target) l++;
                    else if(sum > target) r--;
                    else {
                        result.push_back({nums[i], nums[j], nums[l], nums[r]});
                        l++;
                        r--;
                        while(l < r && nums[l] == nums[l-1]) l++;
                    }
                }
            }
        }
        return result;
    }
};