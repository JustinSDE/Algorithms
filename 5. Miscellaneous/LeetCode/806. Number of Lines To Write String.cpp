class Solution {
  public:
    vector<int> numberOfLines(vector<int> &widths, string S) {
        if (S.empty())
            return {0, 0};
        int lines = 1, chrcnt = 0;
        int chrwidth;
        for (auto ch : S) {
            chrwidth = widths[ch - 'a'];
            if (chrcnt + chrwidth > 100) {
                lines++;
                chrcnt = chrwidth;
                continue;
            } else
                chrcnt += chrwidth;
        }
        return vector<int>{lines, chrcnt};
    }
};