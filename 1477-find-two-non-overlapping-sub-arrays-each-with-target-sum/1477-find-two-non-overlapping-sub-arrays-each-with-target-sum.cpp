class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {

        int n = arr.size();
        int INF = n + 1;

        // best[i] = minimum length of a target-sum
        // subarray ending anywhere from 0 to i
        vector<int> best(n, INF);

        int left = 0;
        int sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {

            sum += arr[right];

            // Since all elements are positive
            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            // Current subarray has sum = target
            if (sum == target) {

                int currentLength = right - left + 1;

                // Previous subarray must end before 'left'
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, currentLength + best[left - 1]);
                }
            }

            // Carry previous best
            if (right > 0) {
                best[right] = best[right - 1];
            }

            // Store current subarray length
            if (sum == target) {
                int currentLength = right - left + 1;
                best[right] = min(best[right], currentLength);
            }
        }

        return ans == INF ? -1 : ans;
    }
};