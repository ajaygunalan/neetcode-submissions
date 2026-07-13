class Solution {
public:
    int climbStairs(int n) {
        vector<int> W(n + 2, 0);            // ways-to-go; W[n] = 1 — the top: one way to be there
        W[n] = 1;
        for (int i = n - 1; i >= 0; i--)    // backward sweep: solve short tails first
            W[i] = W[i+1] + W[i+2];         // counting: SUM over roads — no toll, nothing to min
        return W[0];                        // one start state — read its board
    }
};
