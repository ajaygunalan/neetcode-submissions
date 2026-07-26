class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
        sort(nums.begin(), nums.end());
        set<vector<int>> found;

        for(int i=0; i<nums.size();  i++) {
            unordered_set<int> seen;

            for(int j=i+1;  j<nums.size(); j++){
                int complement = -nums[i] - nums[j];
                if(seen.count(complement))
                    found.insert({nums[i], complement, nums[j]});
                seen.insert(nums[j]);
            }

        }
        return vector<vector<int>>(found.begin(), found.end());
    }
};