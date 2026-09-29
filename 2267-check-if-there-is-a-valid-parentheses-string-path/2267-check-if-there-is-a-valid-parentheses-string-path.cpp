class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Total path length must be even
        if ((m + n - 1) % 2 == 1)
            return false;

        // dp[i][j] = possible balances at (i,j)
        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(m + n, false))
        );

        // Starting cell must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                int change = (grid[i][j] == '(') ? 1 : -1;

                for (int balance = 0; balance < m + n; balance++) {

                    int prev = balance - change;

                    if (prev < 0)
                        continue;

                    // Come from top
                    if (i > 0 && dp[i - 1][j][prev])
                        dp[i][j][balance] = true;

                    // Come from left
                    if (j > 0 && dp[i][j - 1][prev])
                        dp[i][j][balance] = true;
                }
            }
        }

        // Valid string must finish with balance 0
        return dp[m - 1][n - 1][0];
    }
};