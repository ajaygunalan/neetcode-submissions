  class Solution {
  public:
      int search(vector<int>& nums, int target) {
          int pivot = findPivot(nums);
          int l, r, n = nums.size();
          
          if(target <= nums[n-1]) 
            l=pivot, r=n-1;
          else 
            l=0, r=pivot-1;
          
          while(l <= r) {
              int m = l + (r-l)/2;
              if(nums[m] == target) return m;
              else if(nums[m] > target) r=m-1;
              else l=m+1;
          }
          
          return -1;
      }
  private:
      int findPivot(vector<int>& nums) {
          int l=0, r=nums.size()-1;
          while(l < r) {
              int m = l + (r-l)/2;
              (nums[m] > nums[r]) ? l=m+1 : r=m;
          }
          return l;
      }
  };




