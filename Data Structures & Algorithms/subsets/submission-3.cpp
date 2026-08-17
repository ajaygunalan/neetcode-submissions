class Solution {
    vector<vector<int>> result;
    vector<int> path;
    vector<int>* numsPtr;
    
    void backtrack(int i) {
        vector<int>& nums = *numsPtr;
        result.push_back(path);
        for(i; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(i+1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        numsPtr = &nums;
        backtrack(0);
        return result;
    }
};



// choose 1 -> [1], 
// --------- choose 2 -> [1, 2],  
//-------------------------------choose 3- >[1, 2, 3]
// ----------- unchoose 2 -> [1, 3]


// unchoose 1 -> 
//--------- choose 2 ->  [2], 
//-----------------------------choose 3 -> [2,3]
//--------- unchoose 2 ->  [3]