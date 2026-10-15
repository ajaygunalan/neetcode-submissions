class Solution {
  public:
      void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            auto freeSlots = nums1.begin() + m;
            ranges::copy(nums2, freeSlots);
            inplace_merge(nums1.begin(), freeSlots, nums1.end());
      }
  };
