class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // Put numbers in ascending order
        sort(nums.begin(), nums.end());

        int currentLength = 1;
        int longestLength = 1;

        for (int i = 1; i < nums.size(); i++) {

            // Case 1: Duplicate number — ignore it
            if (nums[i] == nums[i - 1]) {
                continue;
            }

            // Case 2: Consecutive number — increase sequence length
            if (nums[i] == nums[i - 1] + 1) {
                currentLength++;
            }

            // Case 3: Gap found — start a new sequence
            else {
                currentLength = 1;
            }

            longestLength = max(longestLength, currentLength);
        }

        return longestLength;
    }
};