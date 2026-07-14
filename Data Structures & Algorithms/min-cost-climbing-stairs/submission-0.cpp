class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> V(n + 1);
        V[n]   = 0;                             // goal: a finished trip costs nothing
        V[n-1] = cost[n-1];                     // last stair: pay it, both actions finish
        for (int i = n - 2; i >= 0; i--)        // backward sweep, n-1 iterations
            V[i] = cost[i] + min(V[i+1], V[i+2]);   // combine roads: pay, then MIN
        return min(V[0], V[1]);                 // read the start board(s)
    }
};