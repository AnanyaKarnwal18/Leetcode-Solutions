class Solution {
public:
    static const long long MOD = 1000000007;

    long long power(long long a, long long b) {
        long long ans = 1;

        while (b > 0) {
            if (b & 1)
                ans = (ans * a) % MOD;

            a = (a * a) % MOD;
            b >>= 1;
        }

        return ans;
    }

    long long combination(int n, int r) {
        if (r < 0 || r > n)
            return 0;

        long long factN = 1;
        long long factR = 1;
        long long factNR = 1;

        for (int i = 1; i <= n; i++)
            factN = (factN * i) % MOD;

        for (int i = 1; i <= r; i++)
            factR = (factR * i) % MOD;

        for (int i = 1; i <= n - r; i++)
            factNR = (factNR * i) % MOD;

        long long invR = power(factR, MOD - 2);
        long long invNR = power(factNR, MOD - 2);

        return (((factN * invR) % MOD) * invNR) % MOD;
    }

    int numberOfSets(int n, int k) {
        return combination(n + k - 1, 2 * k);
    }
};