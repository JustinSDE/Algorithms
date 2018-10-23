class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty())
            return 0;
        map<char, int> count;
        int res=1, sz=s.length();
        int left=0, right=0;
        while(right<sz){
            char currentChar;
            do{
                currentChar = s[right];
                count[currentChar]++;
                right++;
            }while(count[currentChar]==1 && right<sz);
            if(count[currentChar]==1){
                res=max(res, right-left);
            }
            else{
                res=max(res, right-left-1);
            }
            if(right==sz)
                break;
            do{
                currentChar=s[left];
                count[currentChar]--;
                left++;
            }while(count[currentChar]!=1);
        }
        return res;
        
    }
};



class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        int sz=s.size();
        if(sz<2)
            return sz;
        vector<int> pos(256,-1);
        int result=0, start=0;
        for(int i=0; i<sz; i++){
            if(start<=pos[s[i]]){
                start=pos[s[i]]+1;
            }
            result = max(result, i-start+1);
            pos[s[i]]=i;
        }
        return result; 
    }
};
