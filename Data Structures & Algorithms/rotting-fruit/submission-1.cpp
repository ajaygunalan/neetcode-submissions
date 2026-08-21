class Solution {
private:
    int rows, cols, fresh;
    queue<pair<int, int>> q;

public:
    int orangesRotting(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();

        // 1. reset the members — LeetCode reuses one object across all test cases
        fresh = 0;
        q = {};

        // 2. one scan: count what must rot, queue every fruit already rotten
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1)
                    fresh++;
                if (grid[r][c] == 2)
                    q.push({r, c});
            }
        }

        // 3. no fresh fruit at all — no time passes
        if (fresh == 0)
            return 0;

        int minutes = 0;

        // 4. each pass of this loop is one minute
        while (!q.empty() && fresh > 0) {
            // 4.1 how many fruits belong to this minute — read before any pop
            int size = q.size();

            // 5. drain exactly this generation
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();
                spread(grid, r, c);
            }

            // 6. the generation is gone — one minute has elapsed
            minutes++;
        }

        // 7. fruit still fresh was walled off by empty cells
        return fresh == 0 ? minutes : -1;
    }

    void spread(vector<vector<int>>& grid, int r, int c) {
        // 8. the four neighbours: up, down, left, right
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            // 9. off the grid, or not a fresh fruit
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            if (grid[nr][nc] != 1)
                continue;

            // 10. rot it — this also marks it seen, so it can't be queued twice
            grid[nr][nc] = 2;
            fresh--;
            q.push({nr, nc});
        }
    }
};