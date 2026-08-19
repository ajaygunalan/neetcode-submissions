class Solution {
private:
    vector<vector<int>> heights;
    vector<vector<bool>> pacific;
    vector<vector<bool>> atlantic;
    int m, n;

    void dfs(int r, int c, int prevHeight, vector<vector<bool>>& ocean) {
        if (r < 0 || r >= m || c < 0 || c >= n) return;
        if (heights[r][c] < prevHeight) return;
        if (ocean[r][c]) return;
        ocean[r][c] = true;
        static constexpr pair<int,int> dirs[4] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto [dr, dc] : dirs)
            dfs(r + dr, c + dc, heights[r][c], ocean);
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        this->heights = heights;
        m = heights.size();
        n = heights[0].size();

        pacific  = vector<vector<bool>>(m, vector<bool>(n, false));
        atlantic = vector<vector<bool>>(m, vector<bool>(n, false));

        for (int r = 0; r < m; r++) {
            dfs(r, 0, 0, pacific); // left edge  → Pacific
            dfs(r, n - 1, 0, atlantic); // right edge → Atlantic
        }
        for (int c = 0; c < n; c++) {
            dfs(0, c, 0, pacific); // top edge    → Pacific
            dfs(m - 1, c, 0, atlantic);  // bottom edge → Atlantic
        }

        vector<vector<int>> result;
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (pacific[r][c] && atlantic[r][c])
                    result.push_back({r, c});

        return result;
    }
};