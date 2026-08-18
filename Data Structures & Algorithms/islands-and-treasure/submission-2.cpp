class Solution {
private:
    vector<vector<int>>* grid;
    int m, n;
    queue<pair<int, int>> q;
    const vector<pair<int, int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

    void bfs() {
        while(!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            for(auto [dr, dc] : dirs) {
                int r = row + dr;
                int c = col + dc;
                if(r<0 || r>=m || c<0 || c>=n || ((*grid)[r][c] != INT_MAX))
                    continue;
                (*grid)[r][c] = (*grid)[row][col] + 1;
                q.push({r, c}); 
            }
        }
    }


public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        this->grid = &grid;
        m = this->grid->size();
        n = (*this->grid)[0].size();

        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if(grid[i][j] == 0)
                    q.push({i, j});
        bfs();
    }
};