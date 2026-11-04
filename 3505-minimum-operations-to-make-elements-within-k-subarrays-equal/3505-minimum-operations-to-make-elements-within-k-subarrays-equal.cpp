
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        multiset<long long> low, high;

        long long sumLow = 0, sumHigh = 0;

        // Insert element into the sliding window
        auto add = [&](long long val) {

            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            }
            else {
                high.insert(val);
                sumHigh += val;
            }

            // Balance the two halves
            while (low.size() > high.size() + 1) {
                long long v = *low.rbegin();

                low.erase(prev(low.end()));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }

            while (low.size() < high.size()) {
                long long v = *high.begin();

                high.erase(high.begin());
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        // Remove element from the sliding window
        auto remove = [&](long long val) {

            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            }
            else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            // Balance the two halves
            while (low.size() > high.size() + 1) {
                long long v = *low.rbegin();

                low.erase(prev(low.end()));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }

            while (low.size() < high.size()) {
                long long v = *high.begin();

                high.erase(high.begin());
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        // Calculate cost of making current window equal
        auto getCost = [&]() -> long long {

            long long median = *low.rbegin();

            long long leftCost =
                median * (long long)low.size() - sumLow;

            long long rightCost =
                sumHigh - median * (long long)high.size();

            return leftCost + rightCost;
        };

        vector<long long> cost(n - x + 1);

        // Calculate cost for every window
        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {

            dp[i][0] = 0;

            for (int j = 1; j <= k; j++) {

                // Don't select current position
                dp[i][j] = dp[i - 1][j];

                // Select a window ending at i - 1
                if (i >= x && dp[i - x][j - 1] != INF) {

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
