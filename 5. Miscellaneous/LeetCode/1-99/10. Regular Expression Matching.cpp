class Solution {
  public:
    bool isMatch(string s, string p) {
        int sz_s = s.length(), sz_p = p.length();

        // build a 2D array to store intermediate results
        std::vector<std::vector<bool>> matching_or_not(
            sz_s + 1, std::vector<bool>(sz_p + 1, false));
        // set the last case to 'true', i.e. ""=="";
        matching_or_not[sz_s][sz_p] = true;

        // deal with the corner case
        for (int j = sz_p - 1; j >= 0; j--) {
            if (p[j] == '*') {
                matching_or_not[sz_s][j - 1] = matching_or_not[sz_s][j + 1];
            }
        }

        for (int j = sz_p - 1; j >= 0; j--) {
            if (p[j] == '*')
                continue;
            for (int i = sz_s - 1; i >= 0; i--) {
                if (j < sz_p && p[j + 1] == '*') {
                    // if the next character in the pattern is '*';
                    if (p[j] == '.' || p[j] == s[i]) {
                        matching_or_not[i][j] = matching_or_not[i + 1][j + 2] ||
                                                matching_or_not[i + 1][j];
                    }
                    matching_or_not[i][j] =
                        matching_or_not[i][j + 2] || matching_or_not[i][j];
                } else {
                    // the next character in the pattern is not '*'
                    if (p[j] == '.' || p[j] == s[i])
                        matching_or_not[i][j] = matching_or_not[i + 1][j + 1];
                }
            }
        }
        return matching_or_not[0][0];
    }
};
