class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = find(nums.begin(), nums.end(), 0) - nums.begin();

        bool forward = true;
        bool backward = true;

        for (int j = 0; j < n; j++) {
            if (nums[(zero + j) % n] != j)
                forward = false;

            if (nums[(zero - j + n) % n] != j)
                backward = false;
        }

        int ans = INT_MAX;

        if (forward) {
            ans = min(zero, n - zero + 2);
        }

        if (backward) {
            ans = min(ans, min(n - zero, zero + 2));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};