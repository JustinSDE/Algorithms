class Solution {
  public:
    int arrayPairSum(vector<int> &nums) {
        int maxSum = 0;

        sort(nums.begin(), nums.end());

        const int totalNums = nums.size();
        for (int i = 0; i < totalNums; i += 2)
            maxSum += nums[i];

        return maxSum;
    }
};