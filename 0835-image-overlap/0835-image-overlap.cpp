class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        
        int n = img1.size();
        int ans = 0;

        // Try every possible row shift
        for (int rowShift = -(n - 1); rowShift <= n - 1; rowShift++) {
            
            // Try every possible column shift
            for (int colShift = -(n - 1); colShift <= n - 1; colShift++) {
                
                int count = 0;

                // Check every cell of img1
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        
                        if (img1[i][j] == 1) {
                            
                            int newRow = i + rowShift;
                            int newCol = j + colShift;

                            // Check if the moved position is inside img2
                            if (newRow >= 0 && newRow < n &&
                                newCol >= 0 && newCol < n) {
                                
                                if (img2[newRow][newCol] == 1) {
                                    count++;
                                }
                            }
                        }
                    }
                }

                ans = max(ans, count);
            }
        }

        return ans;
    }
};