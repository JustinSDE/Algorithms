class Solution {
  public:
    int smallestRangeI(vector<int> &A, int K) {
        if (A.empty())
            return 0;
        int maxval = *max_element(A.begin(), A.end()) - K;
        int minval = *min_element(A.begin(), A.end()) + K;
        if (maxval <= minval)
            return 0;
        return maxval - minval;
    }
};