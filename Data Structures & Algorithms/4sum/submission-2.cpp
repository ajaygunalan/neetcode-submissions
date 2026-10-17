  class Solution {
  public:
      vector<vector<int>> fourSum(vector<int>& nums, int target) {
          ranges::sort(nums);
          return kSum(nums, 4, 0, target);
      }

  private:
      static vector<vector<int>> kSum(const vector<int>& nums, int k, int start, long long
  target) {
          if(k == 2) return pairsSummingTo(nums, start, target);

          vector<vector<int>> result;
          for(int i=start; i<nums.size(); i++) {
              if(i > start && nums[i] == nums[i-1]) continue;
              for(vector<int>& rest : kSum(nums, k-1, i+1, target - nums[i])) {
                  rest.insert(rest.begin(), nums[i]);
                  result.push_back(rest);
              }
          }
          return result;
      }

      static vector<vector<int>> pairsSummingTo(const vector<int>& nums, int start, long long
  target) {
          vector<vector<int>> pairs;
          int l = start, r = nums.size()-1;

          while(l < r) {
              long long sum = (long long)nums[l] + nums[r];
              if(sum < target) l++;
              else if(sum > target) r--;
              else {
                  pairs.push_back({nums[l], nums[r]});
                  l++;
                  r--;
                  while(l < r && nums[l] == nums[l-1]) l++;
              }
          }
          return pairs;
      }
  };