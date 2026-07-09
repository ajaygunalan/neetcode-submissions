class Solution {
public:
    int search(vector<int>& nums, int target) {
        int right = nums.size()-1;
        int left = 0;
        while (left <= right) {
            if (nums[(left+right)/2] ==  target)
                return (left+right)/2;
            else if(nums[(left+right)/2] > target)
                right = (left+right)/2 - 1;
            else if(nums[(left+right)/2] < target )
                left = (left+right)/2 + 1;
        }
        return -1;
    }
};
