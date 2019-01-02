// can be further optimized by using some space to precalcuate the lengths of each string

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix="";
        int num_of_str = strs.size();
        if(num_of_str==0)
            return prefix;
        int index = 0;
        while(true){
            bool valid = true;
            if(index>=strs[0].length())
                return prefix;
            for(int i=1;i<num_of_str;i++){
                if(index>=strs[i].length() || strs[i][index]!=strs[0][index]){
                    valid = false;
                    break;
                }
            }
            if(!valid){
                return prefix;
            }
            prefix.push_back(strs[0][index]);
            index++;
        }
    }
};
