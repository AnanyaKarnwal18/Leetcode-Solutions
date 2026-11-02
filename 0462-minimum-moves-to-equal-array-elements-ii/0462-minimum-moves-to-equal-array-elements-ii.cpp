
class Solution {
public:
    int minMoves2(vector<int>& nums) {

        // Step 1: Sort the array
        sort(nums.begin(), nums.end());

        // Step 2: Find the median
        int n = nums.size();
        int median = nums[n / 2];

        // Step 3: Calculate total moves
        long long moves = 0;

        for (int i = 0; i < n; i++) {
            moves += abs((long long)nums[i] - median);
        }

        // Step 4: Return the answer
        return moves;
    }
};
