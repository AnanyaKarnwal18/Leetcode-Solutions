class Solution {
public:
   int countSmallEqual(int m, int n, int mid){
    int count=0;
    for(int i=1;i<=m;i++){
        count += min(n,mid/i);
    }

    return count;
   }

    int findKthNumber(int m, int n, int k) {
         int low = 1;
        int high = m * n;

        while (low < high) {

            int mid = low + (high - low) / 2;

            int count = countSmallEqual(m, n, mid);

            if (count < k)
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }
};