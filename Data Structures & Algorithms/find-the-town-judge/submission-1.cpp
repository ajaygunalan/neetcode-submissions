class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> arrow_in(n+1, 0);
        for (vector<int> pair : trust) {
            arrow_in[pair[0]]--;
            arrow_in[pair[1]]++;
        }

        for(int i = 1; i <= n; i++)
            if(arrow_in[i] == n-1) 
                return i;
        return -1;
    }
};

