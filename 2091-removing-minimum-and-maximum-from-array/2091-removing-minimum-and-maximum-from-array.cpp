class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minI= 0;
        int maxI=0;

        for(int i =1; i<n ; i++){
         if(nums[i]<nums[minI])
         minI = i;
        
         if(nums[i]>nums[maxI])
         maxI = i;
        
    }
    // Case 1: both from front
        int front = max(minI, maxI )+ 1;

        // Case 2: both from back
        int back = n - min(minI, maxI);

        // Case 3: min from front, max from back
        int mixed1 = minI + 1 + n - maxI;

        // Case 4: max from front, min from back
        int mixed2 = maxI + 1 + n - minI;

        return min({front, back, mixed1, mixed2});
    }
};