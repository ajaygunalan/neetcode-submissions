class Solution {
private:
    vector<vector<int>> grid;
    int rows, cols;
    int dfs(int r, int c) {
        if(r<0 || r>=rows || c<0 || c>=cols || grid[r][c] != 1) return 0;
        grid[r][c] = 0;
        
        return  1 
        + dfs(r+1, c) 
        + dfs(r-1, c)
        + dfs(r, c+1)
        + dfs(r, c-1);
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        this->grid = std::move(grid);
        rows = this->grid.size();
        cols = this->grid[0].size();
        int maxArea=0;
        for(int r=0; r<rows; r++)
            for(int c=0; c<cols; c++)
                if(this->grid[r][c] == 1)
                    maxArea = max(dfs(r,c), maxArea);
        return maxArea;
    }
};
