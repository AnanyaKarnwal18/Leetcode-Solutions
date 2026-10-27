class Solution {
public:
vector<string> result;
void generate(int n , int open , int close, string curr){
    if(open== n && close==n){
        result.push_back(curr);
        return;
    }
    if(open<n){
        generate(n,open + 1, close, curr + '(');
    }
    if(close<open){
        generate(n,open, close + 1, curr + ')');
    }
}


    vector<string> generateParenthesis(int n) {
        generate(n,0,0,"");
        return result;
    }
};