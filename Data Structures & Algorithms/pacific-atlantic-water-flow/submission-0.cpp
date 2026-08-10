class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& inputs) {
        // 1. stop before accessing heights[0] when the grid is empty
        if (inputs.empty() || inputs[0].empty())
            return {};

        // 2. copy the input into the member grid so DFS needs no grid parameter
        heights = inputs;
        rows = heights.size();
        cols = heights[0].size();

        // 3. record which cells can reach each ocean
        vector<vector<bool>> canReachPacific(rows, vector<bool>(cols, false));
        vector<vector<bool>> canReachAtlantic(rows, vector<bool>(cols, false));

        // 4. search backward from the left-Pacific and right-Atlantic borders
        for (int r = 0; r < rows; r++) 
            dfs(r, 0, heights[r][0], canReachPacific),
            dfs(r, cols - 1, heights[r][cols - 1], canReachAtlantic);

        // 5. search backward from the top-Pacific and bottom-Atlantic borders
        for (int c = 0; c < cols; c++)  
            dfs(0, c, heights[0][c], canReachPacific), 
            dfs(rows - 1, c, heights[rows - 1][c], canReachAtlantic);


        // 6. collect cells reached from both oceans
        vector<vector<int>> result;

        for (int r = 0; r < rows; r++) 
            for (int c = 0; c < cols; c++) 
                if (canReachPacific[r][c] && canReachAtlantic[r][c]) 
                    result.push_back({r, c});

        // 7. return the collected coordinates
        return result;
    }

private:
    int rows, cols;
    // A normal member vector can be assigned inside pacificAtlantic
    vector<vector<int>> heights;

    void dfs(int r,
             int c,
             int previousHeight,
             vector<vector<bool>>& canReachOcean) {

        // 8. stop when:
        //    8.1 the cell is outside the grid
        //    8.2 this ocean has already visited the cell
        //    8.3 reverse DFS would move to a lower cell
        if (r < 0 || r >= rows ||
            c < 0 || c >= cols ||
            canReachOcean[r][c] ||
            heights[r][c] < previousHeight) return;
    

        // 9. record that this cell can reach the current ocean
        canReachOcean[r][c] = true;

        // 10. use this height while checking the neighboring cells
        int currentHeight = heights[r][c];

        // 11. recursively search the four adjacent cells
        dfs(r - 1, c, currentHeight, canReachOcean);
        dfs(r + 1, c, currentHeight, canReachOcean);
        dfs(r, c - 1, currentHeight, canReachOcean);
        dfs(r, c + 1, currentHeight, canReachOcean);
    }
};