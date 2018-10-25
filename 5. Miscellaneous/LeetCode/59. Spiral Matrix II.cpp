class Solution {
  public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int top = 0, left = 0, bottom = n - 1, right = n - 1;
        int val = 1, side = 0, i;
        while (top <= bottom && left <= right) {
            switch (side % 4) {
            case 0:
                for (i = left; i <= right; i++) {
                    matrix[top][i] = val;
                    val++;
                }
                top++;
                break;
            case 1:
                for (i = top; i <= bottom; i++) {
                    matrix[i][right] = val;
                    val++;
                }
                right--;
                break;
            case 2:
                for (i = right; i >= left; i--) {
                    matrix[bottom][i] = val;
                    val++;
                }
                bottom--;
                break;
            case 3:
                for (i = bottom; i >= top; i--) {
                    matrix[i][left] = val;
                    val++;
                }
                left++;
                break;
            default:
                break;
            }
            side = (side + 1) % 4;
        }
        return move(matrix);
    }
};