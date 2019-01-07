class Solution {
  public:
    bool checkPossibility(vector<int> &nums) {
        bool used = false;
        int sz = nums.size();
        for (int i = 1; i < sz; i++) {
            if (nums[i] >= nums[i - 1])
                continue;
            else {
                if (used)
                    return false;
                used = true;
                if (i == 1)
                    continue;
                if (i == sz - 1)
                    continue;
                if (nums[i - 2] <= nums[i])
                    continue;
                else
                    nums[i] = nums[i - 1];
            }
        }
        return true;
    }
};