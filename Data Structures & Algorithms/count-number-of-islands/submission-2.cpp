class Solution {
private:
    vector<vector<char>>* gridPtr;
    int rows, cols;

    bool dfs(int r, int c) {
        vector<vector<char>>& grid = *gridPtr;
        if(r<0 || r>=rows || c<0 || c>=cols || grid[r][c] != '1') return false;
        grid[r][c] = '0';
        dfs(r+1, c);
        dfs(r-1, c);
        dfs(r, c+1);
        dfs(r, c-1);
        return true;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        gridPtr = &grid;
        rows = grid.size();
        cols = grid[0].size();
        int count = 0;
        for(int r=0; r<rows; r++)
            for(int c=0; c<cols; c++)
                if(dfs(r, c))
                    count++;
        return count;
    }
};