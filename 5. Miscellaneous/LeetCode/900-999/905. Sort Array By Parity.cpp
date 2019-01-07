class Solution {
  public:
    vector<int> sortArrayByParity(vector<int> &A) {
        int slow = 0, fast = 0;
        while (fast < A.size()) {
            if (A[fast] % 2 == 0) {
                swap(A[fast], A[slow]);
                slow++;
            }
            fast++;
        }
        return A;
    }
};