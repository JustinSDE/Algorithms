class Solution {
  public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        int totalsize = R * C;
        vector<vector<int>> res;
        if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
            res.push_back(vector<int>{r0, c0});
            totalsize--;
            if (totalsize == 0)
                return res;
        }
        int step_size = 1;
        while (true) {
            for (int i = 0; i < step_size; i++) {
                c0++;
                if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                    res.push_back(vector<int>{r0, c0});
                    totalsize--;
                    if (totalsize == 0)
                        return res;
                }
            }
            for (int i = 0; i < step_size; i++) {
                r0++;
                if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                    res.push_back(vector<int>{r0, c0});
                    totalsize--;
                    if (totalsize == 0)
                        return res;
                }
            }
            step_size++;
            for (int i = 0; i < step_size; i++) {
                c0--;
                if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                    res.push_back(vector<int>{r0, c0});
                    totalsize--;
                    if (totalsize == 0)
                        return res;
                }
            }
            for (int i = 0; i < step_size; i++) {
                r0--;
                if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                    res.push_back(vector<int>{r0, c0});
                    totalsize--;
                    if (totalsize == 0)
                        return res;
                }
            }
            step_size++;
        }
    }
};