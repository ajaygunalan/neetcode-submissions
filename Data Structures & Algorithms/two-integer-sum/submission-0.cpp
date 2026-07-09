class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> a;
        for (int i = 0; i < nums.size(); i++) {
            if (a.count(target - nums[i]))
                return {a[target - nums[i]], i};
            a[nums[i]] = i;
        }
        return {};
    }
};
