class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int c1 = 0, n1 = 0, c2 = 0, n2 = 0;
        for(int i=0; i<n; i++) {
            if(nums[i] == c1) n1++;
            else if(nums[i] == c2) n2++;
            else if(n1 == 0) c1 = nums[i], n1 = 1;
            else if(n2 == 0) c2 = nums[i], n2 = 1 ;
            else n1--, n2--;
        }
        vector<int> res;
        if(ranges::count(nums, c1) > n/3) res.push_back(c1);
        if(c2 != c1 && ranges::count(nums, c2) > n/3) res.push_back(c2);
        return res;
    }
};