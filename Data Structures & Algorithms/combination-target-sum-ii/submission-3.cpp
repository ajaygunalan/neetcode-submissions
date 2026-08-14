class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<int>* candidatesPtr;
    int target;

    void backtrack(int sum, int start) {
        vector<int>& nums = *candidatesPtr;
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
        candidatesPtr = &candidates;
        backtrack(0, 0);
        return result;
    }
};
