class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        long long total = 0;

        for (int num : nums) {
            total += num;
        }

        long long target = total - x;

        // If target is negative, impossible
        if (target < 0) {
            return -1;
        }

        // If target is 0, we have to remove all elements
        if (target == 0) {
            return n;
        }

        int left = 0;
        long long sum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {

            sum += nums[right];

            // Make sum <= target
            while (left <= right && sum > target) {
                sum -= nums[left];
                left++;
            }

            // Found a subarray with required sum
            if (sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        if (maxLen == -1) {
            return -1;
        }

        return n - maxLen;
    }
};