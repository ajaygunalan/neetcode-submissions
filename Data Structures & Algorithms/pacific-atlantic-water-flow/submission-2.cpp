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
        dfs(r + 1, c, heights[r][c], ocean);
        dfs(r - 1, c, heights[r][c], ocean);
        dfs(r, c + 1, heights[r][c], ocean);
        dfs(r, c - 1, heights[r][c], ocean);
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        this->heights = heights;
        m = heights.size();
        n = heights[0].size();

        pacific  = vector<vector<bool>>(m, vector<bool>(n, false));
        atlantic = vector<vector<bool>>(m, vector<bool>(n, false));

        vector<pair<int,int>> pacificStarts;
        for (int r = 0; r < m; r++)
            pacificStarts.push_back({r, 0});
        for (int c = 0; c < n; c++)
            pacificStarts.push_back({0, c});

        vector<pair<int,int>> atlanticStarts;
        for (int r = 0; r < m; r++)
            atlanticStarts.push_back({r, n - 1});
        for (int c = 0; c < n; c++)
            atlanticStarts.push_back({m - 1, c});

        for (auto [r, c] : pacificStarts)
            dfs(r, c, 0, pacific);
        for (auto [r, c] : atlanticStarts)
            dfs(r, c, 0, atlantic);

        vector<vector<int>> result;
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (pacific[r][c] && atlantic[r][c])
                    result.push_back({r, c});

        return result;
    }
};