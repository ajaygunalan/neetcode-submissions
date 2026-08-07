class Solution {
public:
    vector<int> nums_;
    vector<int> path;
    vector<vector<int>> result;

    void backtrack(int i){
        if(path.size() <= nums_.size())
            result.push_back(path);

        for(i; i<nums_.size(); i++) {
            path.push_back(nums_[i]);
            backtrack(i+1);
            path.pop_back();
        }
        
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        nums_ = nums;
        backtrack(0);
        return result;
    }
};
