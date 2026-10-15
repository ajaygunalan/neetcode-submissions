class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto leftOver = ranges::unique(nums);
        return nums.size() - leftOver.size();
        
    }
};