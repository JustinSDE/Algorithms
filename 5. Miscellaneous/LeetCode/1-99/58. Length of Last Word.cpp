class Solution {
public:
    int lengthOfLastWord(string s) {
        int index = s.length()-1;
        while(index>=0 && s[index]==' ')
            index--;
        int index2 = index;
        while(index2>=0 && s[index2]!=' ')
            index2--;
        return index-index2;
    }
};
