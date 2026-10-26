
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        // Four possible directions: up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Start DFS if this is an unvisited land cell
                if (grid[i][j] > 0) {
                    long long sum = 0;

                    stack<pair<int, int>> st;
                    st.push({i, j});

                    // Mark visited by changing the cell to 0
                    sum += grid[i][j];
                    grid[i][j] = 0;

                    while (!st.empty()) {
                        auto [r, c] = st.top();
                        st.pop();

                        // Explore all four neighbours
                        for (int d = 0; d < 4; d++) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];

                            // Check grid boundaries
                            if (nr >= 0 && nr < m &&
                                nc >= 0 && nc < n &&
                                grid[nr][nc] > 0) {

                                sum += grid[nr][nc];

                                st.push({nr, nc});

                                // Prevent revisiting this cell
                                grid[nr][nc] = 0;
                            }
                        }
                    }

                    // Count this island if its sum is divisible by k
                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};
