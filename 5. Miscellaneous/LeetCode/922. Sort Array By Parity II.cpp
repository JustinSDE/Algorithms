class Solution {
  public:
    vector<int> sortArrayByParityII(vector<int> &A) {
        int evenindex = 0, oddindex = 1;
        while (true) {
            while (evenindex < A.size() && A[evenindex] % 2 == 0)
                evenindex += 2;
            while (oddindex < A.size() && A[oddindex] % 2 == 1)
                oddindex += 2;
            if (evenindex >= A.size() || oddindex >= A.size()) {
                break;
            }
            swap(A[evenindex], A[oddindex]);
        }
        return A;
    }
};