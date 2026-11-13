  class Solution {
  public:
      int search(vector<int>& nums, int target) {
        int pivot = findPivotMin(nums);
        auto [l, r] = pickLine(nums, pivot, target)
        return binarySearch(nums, l, r, target);
      }
  private:
      int findPivotMin(vector<int>& nums) {
          int l=0, r=nums.size()-1;
          while(l < r) {
              int m = l + (r-l)/2;
              (nums[m] > nums[r]) ? l=m+1 : r=m;
          }
          return l;
      }

      pair<int, int> pickLine(vector<int>& nums, int pivot, int target) {
        int n =  nums.size();
        if(target <= nums[n-1]) return {pivot, n-1};
        return {0, pivot-1};
      }
      int binarySearch(vector<int>& nums, int l, int r, int target) {
        while(l <= r) {
            int m = l +(r-l)/2;
            if(nums[m] == target) return m;
            else if(nums[m] > target) r= m-1;
            else l = m+1;
        }
        return -1;
      }
  };




        //   int pivot = findPivot(nums);
        //   int l, r, n = nums.size();
          
        //   if(target <= nums[n-1]) 
        //     l=pivot, r=n-1;
        //   else 
        //     l=0, r=pivot-1;
          
        //   while(l <= r) {
        //       int m = l + (r-l)/2;
        //       if(nums[m] == target) return m;
        //       else if(nums[m] > target) r=m-1;
        //       else l=m+1;
        //   }
        //   return -1;