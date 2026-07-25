class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            if(seen.count(target-num))
                return {seen[target-num], i};
            seen[nums[i]] = i;
        }
        return {};
    }
};