/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:

    int findPeak(MountainArray &arr, int n) {
        int low = 0, high = n - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr.get(mid) < arr.get(mid + 1))
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

    int binarySearchAscending(MountainArray &arr, int low, int high, int target) {

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr.get(mid) == target)
                return mid;

            if (arr.get(mid) < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }

    int binarySearchDescending(MountainArray &arr, int low, int high, int target) {

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr.get(mid) == target)
                return mid;

            if (arr.get(mid) > target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }

    int findInMountainArray(int target, MountainArray &mountainArr) {

        int n = mountainArr.length();

        // Find peak
        int peak = findPeak(mountainArr, n);

        //  Search left/ascending side
        int ans = binarySearchAscending(
            mountainArr, 0, peak, target
        );

        if (ans != -1)
            return ans;

        //  Search right/descending side
        return binarySearchDescending(
            mountainArr, peak + 1, n - 1, target
        );
    }
};