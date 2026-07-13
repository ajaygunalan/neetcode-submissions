class Solution {
public:
    int climbStairs(int n) {
        // W(i) = the board on stair i:
        //        number of distinct trips from HERE to the top.
        vector<int> W(n + 2, 0);
        W[n]     = 1;   // the top: trivial tail — you're there (Delhi, V = 0's cousin)
        W[n - 1] = 1;   // one road left: a single 1-step (Jaipur/Lucknow stage)

        // THE SWEEP RUNS BACKWARDS — solve short tails first
        for (int i = n - 2; i >= 0; i--) {
            //       1-step road   2-step road
            W[i] =   W[i + 1]  +   W[i + 2];
            // counting, not optimizing → SUM over roads instead of min.
            // Everything beyond the next stair is already inside the neighbour's board.
        }
        return W[0];    // stair 0 = Chennai: the full problem, one lookup
    }
};
