class Solution {
private:
    vector<vector<char>> grid;
    int count =0;
    int rows;
    int cols;

    void dfs(int r, int c) {
        //stop at boundaries, water or already visted
        if(r<0 || r>=rows || c<0 || c>=cols|| grid[r][c] != '1') return;
        // Mark this land as visisted
        grid[r][c] = '0';
    
        dfs(r+1, c);
        dfs(r-1, c);
        dfs(r, c+1);
        dfs(r, c-1);
    }

public:
    int numIslands(vector<vector<char>>& inputGrid) {
        grid =  inputGrid;
        rows = grid.size();
        cols = grid[0].size();
        
        for(int r=0; r<rows; r++){
            for(int c=0; c<cols; c++) {
                if(grid[r][c] == '1') {
                    count++;
                    dfs(r, c);
                }

            }
        }
        return count;
    }

};
