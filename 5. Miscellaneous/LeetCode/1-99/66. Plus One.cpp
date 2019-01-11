class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int sz = digits.size();
        int carry = 1;
        int i = sz - 1;
        while(carry && i>=0){
            if(digits[i]==9){
                digits[i]=0;
            }
            else{
                digits[i]++;
                carry = 0;
            }
            i--;
        }
        if(carry == 0){
            return digits;
        }
        else{
            vector<int> ret;
            ret.push_back(1);
            for(auto x:digits){
                ret.push_back(x);
            }
            return ret;
        }
    }
};
