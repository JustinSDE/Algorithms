class Solution {
  public:
    int numIslands(vector<vector<char>> &grid) {
        row_count = grid.size();
        if (row_count == 0) {
            return 0;
        }
        col_count = grid[0].size();
        if (col_count == 0) {
            return 0;
        }
        int count = 0;
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < col_count; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    reset(grid, i, j);
                }
            }
        }
        return count;
    }
    void reset(vector<vector<char>> &grid, int i, int j) {
        if (i >= 0 && i < row_count && j >= 0 && j < col_count &&
            grid[i][j] == '1') {
            grid[i][j] = '0';
            reset(grid, i - 1, j);
            reset(grid, i + 1, j);
            reset(grid, i, j - 1);
            reset(grid, i, j + 1);
        }
    }

  private:
    int row_count, col_count;
};