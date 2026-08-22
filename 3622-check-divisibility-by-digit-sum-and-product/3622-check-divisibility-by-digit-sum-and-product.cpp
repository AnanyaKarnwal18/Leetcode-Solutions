class Solution {
public:
    bool checkDivisibility(int n) {
        int temp=n; 
        int product=1;
        int sum=0;
        while(temp>0){
            int digit= temp%10;
            sum += digit;
            product *= digit;
            temp/=10;
        }
        return n % (sum + product)==0;
    }
};