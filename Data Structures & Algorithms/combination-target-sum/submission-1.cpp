class Solution {
public:
    vector<int> nums_;
    int target_;

    vector<int> path;
    vector<vector<int>> result;

    void backtrack(int sum ,int  i) {
        if(sum == target_) {
            result.push_back(path);
            return;
        }
        for(int j = i; j <nums_.size(); j++){
            if(nums_[j] + sum > target_) break;
            path.push_back(nums_[j]);
            backtrack(sum + nums_[j], j);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        nums_ = nums;
        target_ = target;
        sort(nums_.begin(), nums_.end());
        backtrack(0, 0);
        return result;
    }
};


//    vector<int> nums_;
//     int target_;
//     vector<int> path;
//     vector<vector<int>> result;


//     void backtrack(int i, int sum){
//         if (sum == target_) {
//             result.push_back(path);
//             return;
//         }
//         else if(sum > target_) 
//             return;

//         for(int j=i; j<nums_.size(); j++) {
//             path.push_back(nums_[j]);
//             backtrack(j, sum + nums_[j]);
//             path.pop_back();

//         }

//     }

// public:
//     vector<vector<int>> combinationSum(vector<int>& nums, int target) {
//         nums_ = nums;
//         target_ = target;
//         backtrack(0, 0);
//         return result;
//     }