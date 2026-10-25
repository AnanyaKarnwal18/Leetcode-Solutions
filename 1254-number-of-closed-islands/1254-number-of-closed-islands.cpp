
class Solution {
public:
    int m, n;

    bool dfs(vector<vector<int>>& grid, int r, int c) {
        // If we go outside the grid, this island is not closed
        if (r < 0 || c < 0 || r >= m || c >= n)
            return false;

        // Water or an already visited cell
        if (grid[r][c] == 1)
            return true;

        // Mark this land cell as visited
        grid[r][c] = 1;

        // Explore all four directions
        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);

        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    if (dfs(grid, i, j))
                        count++;
                }
            }
        }

        return count;
    }
};
