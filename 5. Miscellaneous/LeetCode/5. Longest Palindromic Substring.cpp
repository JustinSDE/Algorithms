class Solution {
  public:
    string longestPalindrome(string s) {
        if (s.empty())
            return "";
        int maxlen = 0, maxstart, maxend;
        int curlen, start, end;
        int sz = s.size();
        for (int i = sz / 2; i >= 0; i--) {
            if (i * 2 + 1 < maxlen)
                break;
            // odd
            curlen = 0;
            start = i + 1;
            end = i - 1;
            while (start - 1 >= 0 && end + 1 < sz &&
                   s[start - 1] == s[end + 1]) {
                start--;
                end++;
            }
            curlen = end - start + 1;
            if (curlen > maxlen) {
                maxlen = curlen;
                maxstart = start;
                maxend = end;
            }
            // even
            start = i + 1;
            end = i;
            while (start - 1 >= 0 && end + 1 < sz &&
                   s[start - 1] == s[end + 1]) {
                start--;
                end++;
            }
            curlen = end - start + 1;
            if (curlen > maxlen) {
                maxlen = curlen;
                maxstart = start;
                maxend = end;
            }
        }
        for (int i = sz / 2 + 1; i < sz; i++) {
            if ((sz - i + 1) * 2 + 1 < maxlen)
                break;
            // odd
            curlen = 1;
            start = i;
            end = i;
            while (start - 1 >= 0 && end + 1 < sz &&
                   s[start - 1] == s[end + 1]) {
                start--;
                end++;
            }
            curlen = end - start + 1;
            if (curlen > maxlen) {
                maxlen = curlen;
                maxstart = start;
                maxend = end;
            }
            // even
            start = i + 1;
            end = i;
            while (start - 1 >= 0 && end + 1 < sz &&
                   s[start - 1] == s[end + 1]) {
                start--;
                end++;
            }
            curlen = end - start + 1;
            if (curlen > maxlen) {
                maxlen = curlen;
                maxstart = start;
                maxend = end;
            }
        }
        return s.substr(maxstart, maxlen);
    }
};