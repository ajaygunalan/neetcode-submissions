class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        ranges::sort(nums);
        vector<vector<int>> result;

        for(int i=0; i<nums.size(); i++) {
            unordered_set<int> seen;
            for(int j=i+1; j<nums.size(); j++) {
                int compliment = -(nums[i] + nums[j]);
                if(seen.contains(compliment))
                    result.push_back({nums[i], nums[j], compliment});
                seen.insert(nums[j]);
            }
        }

        ranges::sort(result);
        ranges::subrange duplicates = ranges::unique(result);
        result.erase(duplicates.begin(), duplicates.end());
        return result;
    }
};