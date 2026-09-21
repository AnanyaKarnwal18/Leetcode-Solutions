class Solution {
public:
    int reverseDegree(string s) {
        int sum = 0;

        for (int i = 0; i < s.length(); i++) {
            int normalPosition = s[i] - 'a' + 1;
            int reversePosition = 27 - normalPosition;

            sum += reversePosition * (i + 1);
        }

        return sum;
    }
};