class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    vector<int> nums;
    int target;

    void backtrack(int sum, int i) {
        if (sum == target) {
            result.push_back(path);
            return;
        }

        for (int j = i; j < (int)nums.size(); j++) {
            if (nums[j] + sum > target) break;
            if (j > i && nums[j] == nums[j - 1]) continue;
            path.push_back(nums[j]);
            backtrack(sum + nums[j], j + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int t) {
   
        sort(candidates.begin(), candidates.end());
        nums = candidates;
        target = t;
        backtrack(0, 0);
        return result;
    }
};