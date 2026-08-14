class Solution {
    vector<int> nums;
    int target = 0;
    vector<vector<optional<bool>>> memo;

public:
    bool canPartition(vector<int>& input) {
        int sum = ranges::fold_left(input, 0, plus{});
        if (sum % 2 != 0)
            return false;

        nums = input;
        target = sum / 2;
        int rows = nums.size();
        int cols = target + 1;
        vector<optional<bool>> emptyRow(cols);
        memo.assign(rows, emptyRow);

        return bt(0, 0);
    }

    bool bt(int index, int tempSum) {
        if (tempSum == target)
            return true;
        if (tempSum > target || index >= ssize(nums))
            return false;

        if (memo[index][tempSum].has_value())
            return *memo[index][tempSum];

        bool included = bt(index + 1, tempSum + nums[index]);
        bool excluded = bt(index + 1, tempSum);
        bool found = included || excluded;

        memo[index][tempSum] = found;
        return found;
    }
};