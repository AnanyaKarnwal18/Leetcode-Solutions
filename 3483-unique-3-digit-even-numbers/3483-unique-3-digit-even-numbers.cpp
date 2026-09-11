class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};

        for (int d : digits) {
            cnt[d]++;
        }

        int ans = 0;

        for (int first = 1; first <= 9; first++) {
            for (int middle = 0; middle <= 9; middle++) {
                for (int last = 0; last <= 8; last += 2) {

                    // Temporarily use the digits
                    int need[10] = {};
                    need[first]++;
                    need[middle]++;
                    need[last]++;

                    bool possible = true;

                    for (int d = 0; d <= 9; d++) {
                        if (need[d] > cnt[d]) {
                            possible = false;
                            break;
                        }
                    }

                    if (possible)
                        ans++;
                }
            }
        }

        return ans;
    }
};