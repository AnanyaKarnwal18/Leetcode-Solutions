class Solution {
public:

    int countStudents(vector<int>& arr, int pages) {
        int students = 1;
        long long ps = 0;

        for(int i = 0; i < arr.size(); i++) {
            if(ps + arr[i] <= pages) {
                ps += arr[i];
            }
            else {
                students++;
                ps = arr[i];
            }
        }

        return students;
    }

    int fp(vector<int>& arr, int n, int m) {
        if(m > n) return -1;

        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);

        while(low <= high) {
            int mid = low + (high - low) / 2;

            int students = countStudents(arr, mid);

            if(students > m) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return low;
    }

    int splitArray(vector<int>& nums, int k) {
        return fp(nums, nums.size(), k);
    }
};