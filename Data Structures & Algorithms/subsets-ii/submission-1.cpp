class Solution {
public:
    vector<int> nums_;
    vector<int> path;
    vector<vector<int>> result;

    void backtrack(int i){
        if(path.size() <= nums_.size())
            result.push_back(path);

        for(int j=i; j<nums_.size(); j++) {
            if(j>i && nums_[j] == nums_[j-1]) continue;
            path.push_back(nums_[j]);
            backtrack(j+1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        nums_ = nums;
        sort(nums_.begin(), nums_.end());
        backtrack(0);
        return result;
        
    }
};


