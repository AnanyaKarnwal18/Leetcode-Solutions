class Solution {
private:
    int getDigitSum(int val) {
        int sum = 0;
        while (val > 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        struct Element {
            int digit_sum;
            int val;
            int orig_idx;
        };

        vector<Element> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {getDigitSum(nums[i]), nums[i], i};
        }

        // Sort based on digit_sum first, then value
        sort(arr.begin(), arr.end(), [](const Element& a, const Element& b) {
            if (a.digit_sum != b.digit_sum) {
                return a.digit_sum < b.digit_sum;
            }
            return a.val < b.val;
        });

        vector<bool> visited(n, false);
        int total_swaps = 0;

        for (int i = 0; i < n; ++i) {
            if (visited[i] || arr[i].orig_idx == i) {
                continue;
            }

            int cycle_size = 0;
            int curr = i;

            while (!visited[curr]) {
                visited[curr] = true;
                curr = arr[curr].orig_idx;
                cycle_size++;
            }

            if (cycle_size > 1) {
                total_swaps += (cycle_size - 1);
            }
        }

        return total_swaps;
    }
};