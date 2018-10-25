class Solution {
  public:
    int projectionArea(vector<vector<int>> &grid) {
        int n = grid.size();
        int count = 0;
        for (int i = 0; i < n; i++) {
            int xzmax = 0, yzmax = 0;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 0)
                    count++;
                xzmax = max(xzmax, grid[i][j]);
                yzmax = max(yzmax, grid[j][i]);
            }
            count += yzmax;
            count += xzmax;
        }
        return count;
    }
};