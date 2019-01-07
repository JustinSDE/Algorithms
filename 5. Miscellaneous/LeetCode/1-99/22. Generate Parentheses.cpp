class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string candidate;
        vector<string> result;
        if(n<=0)
            return result;
        generateParenthesisHelper(n,candidate,0,0,result);
        return result;        
    }
    
private:
    void generateParenthesisHelper(int n, string& candidate, int left, int right, vector<string>& result){
        if(candidate.length()==2*n){
            result.push_back(candidate);
            return;
        }
        if(left<n){
            candidate.push_back('(');
            generateParenthesisHelper(n, candidate, left+1, right, result);
            candidate.pop_back();
        }
        if(left>right){
            candidate.push_back(')');
            generateParenthesisHelper(n,candidate,left, right+1, result);
            candidate.pop_back();
        }
        return;
    }
};
