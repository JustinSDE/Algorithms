class Solution {
  public:
    vector<vector<int>> transpose(vector<vector<int>> &A) {
        int row_num = A.size();
        if (row_num == 0)
            return vector<vector<int>>{};
        int col_num = A[0].size();
        vector<vector<int>> ret(col_num, vector<int>(row_num));
        for (int i = 0; i < row_num; i++)
            for (int j = 0; j < col_num; j++) {
                ret[j][i] = A[i][j];
            }
        return ret;
    }
};