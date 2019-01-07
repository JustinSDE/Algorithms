class Solution {
  public:
    string convert(string s, int numRows) {
        if (numRows < 2)
            return s;
        vector<string> intermediate_strs(numRows, "");
        int direction = 1;
        int row = 0;
        for (auto ch : s) {
            intermediate_strs[row].push_back(ch);
            if (row == numRows - 1 && direction == 1) {
                direction = -1;
            } else if (row == 0 && direction == -1) {
                direction = 1;
            }
            row += direction;
        }
        string result = "";
        for (auto &str : intermediate_strs) {
            result += str;
        }
        return result;
    }
};