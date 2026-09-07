
class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;
        int n = s.size();

        vector<long long> dp(n + 1, 0);

        // dp[0] = 1 represents the empty subsequence
        dp[0] = 1;

        // Last occurrence of each character
        vector<int> last(26, -1);

        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';

            // Initially, every old subsequence can either
            // include or exclude s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;

            // If this character appeared before,
            // remove the duplicate subsequences
            if (last[c] != -1) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }

            last[c] = i;
        }

        // Remove the empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
};