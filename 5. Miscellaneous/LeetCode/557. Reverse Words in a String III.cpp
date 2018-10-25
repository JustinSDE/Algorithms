class Solution {
  public:
    string reverseWords(string s) {
        int startIndex = 0, endIndex = 0, sz = s.length();
        while (endIndex != sz) {
            while (endIndex != sz && s[endIndex] != ' ')
                endIndex++;
            reverseWords(s, startIndex, endIndex - 1);
            while (endIndex != sz && s[endIndex] == ' ')
                endIndex++;
            startIndex = endIndex;
        }
        return s;
    }

    void reverseWords(string &s, int start, int end) {
        char temp;
        while (start < end) {
            temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }
};