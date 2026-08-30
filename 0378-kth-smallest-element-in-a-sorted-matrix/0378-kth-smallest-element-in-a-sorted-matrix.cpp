class Solution {
public:
 int countLessEqual(vector<vector<int>>& matrix, int mid) {
    int n = matrix.size();
    int count = 0; 
    for(int i=0;i<n;i++){
    int low =0, high = n-1;
    while ( low <= high){
        int m = low + (high- low)/2;
        if(matrix[i][m]<= mid)
        low = m + 1;

        else
        high = m-1;
    }
count += low;
    }
    return count;
        
    }


    int kthSmallest(vector<vector<int>>& matrix, int k) {
           int n = matrix.size();

       
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (low < high) {

            int mid = low + (high - low) / 2;

           
            int count = countLessEqual(matrix, mid);

            if (count < k) {
                
                low = mid + 1;
            }
            else {
               
                high = mid;
            }
        }

        return low;
        
    }
};