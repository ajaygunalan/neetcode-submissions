class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> seen;

        for(int i=0; i<n; i++)
            seen.insert(nums[i]);
        
        for(int i=0; i<=n; i++)
            if(!seen.count(i))
                return i;
        return -1;
    }
};
