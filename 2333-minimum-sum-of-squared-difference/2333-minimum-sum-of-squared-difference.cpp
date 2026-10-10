
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<long long> diff(n);
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            sum += diff[i];
        }

        if (sum <= k) return 0;

        long long left = 0, right = 100000;

        // Find the minimum possible maximum difference
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long needed = 0;

            for (long long d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed <= k)
                right = mid;
            else
                left = mid + 1;
        }

        long long maxDiff = left;
        long long used = 0;
        long long ans = 0;

        // Reduce every difference to maxDiff
        for (long long d : diff) {
            if (d > maxDiff) {
                used += d - maxDiff;
                d = maxDiff;
            }
            ans += d * d;
        }

        // Distribute remaining operations one at a time.
        // Each such operation reduces one maxDiff to maxDiff - 1.
        long long remaining = k - used;

        // Count elements that are still equal to maxDiff
        for (long long d : diff) {
            if (d > maxDiff) {
                // Original difference was above maxDiff;
                // after reduction it equals maxDiff.
                if (remaining > 0) {
                    ans -= maxDiff * maxDiff
                         - (maxDiff - 1) * (maxDiff - 1);
                    remaining--;
                }
            } else if (d == maxDiff && remaining > 0) {
                ans -= maxDiff * maxDiff
                     - (maxDiff - 1) * (maxDiff - 1);
                remaining--;
            }
        }

        return ans;
    }
};
