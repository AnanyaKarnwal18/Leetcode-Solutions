class Solution {
public:
    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        long long ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;

            for (int start = 0; start < n && ok; start += k) {
                // Check if sorted[start..start+k-1] occurs
                // in the block concatenated with itself.
                vector<int> block(nums.begin() + start,
                                  nums.begin() + start + k);

                vector<int> target(sorted.begin() + start,
                                   sorted.begin() + start + k);

                vector<int> doubled = block;
                doubled.insert(doubled.end(), block.begin(), block.end());

                vector<int> lps(k, 0);
                for (int i = 1, len = 0; i < k;) {
                    if (target[i] == target[len]) {
                        lps[i++] = ++len;
                    } else if (len > 0) {
                        len = lps[len - 1];
                    } else {
                        lps[i++] = 0;
                    }
                }

                bool found = false;
                for (int i = 0, j = 0; i < 2 * k - 1;) {
                    if (doubled[i] == target[j]) {
                        i++;
                        j++;
                        if (j == k) {
                            found = true;
                            break;
                        }
                    } else if (j > 0) {
                        j = lps[j - 1];
                    } else {
                        i++;
                    }
                }

                if (!found) ok = false;
            }

            if (ok) ans += k;
        }

        return ans;
    }
};