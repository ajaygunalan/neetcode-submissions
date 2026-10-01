class Solution {
public:
    set<vector<int>> uniq;      // the extra memory you agreed to pay
    vector<int> path;
    vector<int> nums;
    int target;

    void backtrack(int sum, int i) {
        if (sum == target) {
            uniq.insert(path);  // second [2,6] arrives → set already has it → ignored
            return;
        }
        for (int j = i; j < (int)nums.size(); j++) {
            if (sum + nums[j] > target)
                break;
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
        return vector<vector<int>>(uniq.begin(), uniq.end());
    }
};