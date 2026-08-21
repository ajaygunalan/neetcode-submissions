class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int fresh = 0;
        int minutes = 0;
        queue<pair<int, int>> q;
        int rows = grid.size();
        int cols = grid[0].size();

        for(int r=0; r<rows; r++) {
            for(int c=0; c<cols; c++) {
                if(grid[r][c] == 0) continue;
                if(grid[r][c] == 1) fresh++;
                if(grid[r][c] == 2) q.push({r,c});
            }
        }
        
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0 , -1, 1};

        int size = 0;
        while(!q.empty( ) && fresh > 0) {
            int size = q.size();
            for(int i=0; i<size; i++) {
                auto [r, c] = q.front();
                q.pop();
                for(int d=0; d<4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if(nr<0 || nr>=rows || nc<0 || nc>=cols) continue;
                    if(grid[nr][nc] != 1) continue;
                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
            minutes++;
        }
        return fresh==0 ? minutes : -1;
    }
};
