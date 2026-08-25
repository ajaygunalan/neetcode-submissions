class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        // the one bounds check; off-grid falls out as "not land"
        auto isLand = [&](int r, int c) {
            return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == 1;
        };
        int perimeter = 0;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] == 1)
                    // bool -> int: each land neighbor subtracts 1
                    perimeter += 4 - isLand(r+1,c) - isLand(r-1,c)
                                   - isLand(r,c+1) - isLand(r,c-1);
        return perimeter;
    }
};