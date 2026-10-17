class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        ranges::reverse(nums);
        ranges::reverse(nums | std::views::take(k));
        ranges::reverse(nums | std::views::drop(k));
    }
};