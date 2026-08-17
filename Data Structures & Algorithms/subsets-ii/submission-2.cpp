class Solution {
private:
    vector<int>* numsPtr;
    vector<vector<int>> result;
    vector<int> path;

    void bactrack(int start) {
        vector<int>& nums = *numsPtr;
        result.push_back(path);
        int i = start;
        while(i < nums.size()) {
            if(i > start && nums[i] == nums[i-1]) {
                i++;
                continue;
            }
            path.push_back(nums[i]);
            bactrack(i+1);
            path.pop_back();
            i++;
        }

    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        numsPtr = &nums;
        bactrack(0);
        return result;
    }
};