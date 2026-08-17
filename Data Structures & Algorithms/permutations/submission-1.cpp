class Solution {
private:
    vector<vector<int>> result;
    vector<int>  path;
    vector<int>* numsPtr;
    vector<bool> used; 

    void backtrack() {
        vector<int>& nums = *numsPtr;
        if(path.size() == nums.size()) {
            result.push_back(path);
            return;
        } 
        for(int i=0; i<nums.size(); i++) {
            if(used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtrack();
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        numsPtr = &nums;
        used.assign(nums.size(), false);
        backtrack();
        return result;
    }
};



