class Solution {
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return vector<int>{};
        }
        int top = 0, left = 0, bottom = matrix.size() - 1,
            right = matrix[0].size() - 1;
        int side = 0;
        vector<int> res;
        int i;
        while (top <= bottom && left <= right) {
            switch (side) {
            case 0:
                for (i = left; i <= right; i++) {
                    res.push_back(matrix[top][i]);
                }
                top++;
                break;
            case 1:
                for (i = top; i <= bottom; i++) {
                    res.push_back(matrix[i][right]);
                }
                right--;
                break;
            case 2:
                for (i = right; i >= left; i--) {
                    res.push_back(matrix[bottom][i]);
                }
                bottom--;
                break;
            case 3:
                for (i = bottom; i >= top; i--) {
                    res.push_back(matrix[i][left]);
                }
                left++;
                break;
            default:
                break;
            }
            side = (side + 1) % 4;
        }
        return res;
    }
};