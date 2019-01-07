class Solution {
    
public:
    static vector<string> nums_to_digits; 
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){
            return vector<string>{};
        }
        string candidate;
        vector<string> combinations;
        letterCombinationsHelperFunction(digits, 0, candidate, combinations);
        return combinations;
    }
    
    void letterCombinationsHelperFunction(string& digits, int cur_pos, string& candidate, vector<string>& combinations){
        if(cur_pos==digits.size()){
            combinations.push_back(candidate);
            return;
        }
        int index = digits[cur_pos]-'2';
        for(auto ch:nums_to_digits[index]){
            candidate.push_back(ch);
            letterCombinationsHelperFunction(digits, cur_pos+1, candidate, combinations);
            candidate.pop_back();
        }
        return;
    }
};

vector<string> Solution::nums_to_digits = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
