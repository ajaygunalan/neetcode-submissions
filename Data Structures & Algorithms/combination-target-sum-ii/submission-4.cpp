class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<int> nums;
    int target;

    void backtrack(int sum, int start) {
        if(sum == target) {
            result.push_back(path);
            return;
        }
        int i = start;
        while(i < nums.size()) {
            // Skip duplicates only at the same recursion level
            if(i > start && nums[i] == nums[i-1]) {
                i++;
                continue;
            }
            // All remaining numbers are also too large because nums is sorted
            if(sum + nums[i] > target) break;

            path.push_back(nums[i]);
            backtrack(nums[i]+sum, i+1); // Each element used at most once
            path.pop_back();
            i++;
        }

    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        this->target = target;
        std::ranges::sort(candidates);
        nums = std::move(candidates);
        path.reserve(nums.size());
        backtrack(0, 0);
        return result;
    }
};
