class Solution {
private:
    vector<int> nums;
    int target;
    
    vector<vector<int>> result;
    vector<int> path;

    void backtrack(int sum, int  i) {
        if(sum == target) {
            result.push_back(path);
            return;
        }

        while(i<nums.size()) {
            if(sum + nums[i] > target) return;
            
            path.push_back(nums[i]);
            backtrack(sum + nums[i], i);
            path.pop_back();
            i++;
        }
    }

public:    
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        this->target = target;
        this->nums = nums;
        ranges::sort(this->nums);
        backtrack(0, 0);
        return result;
    }
};