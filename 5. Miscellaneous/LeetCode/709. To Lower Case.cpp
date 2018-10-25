class Solution {
  public:
    string toLowerCase(string str) {
        int sz = str.length();
        int offset = 'a' - 'A';
        for (int i = 0; i < sz; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] += offset;
            }
        }
        return str;
    }
};