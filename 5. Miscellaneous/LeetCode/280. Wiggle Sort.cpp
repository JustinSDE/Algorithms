class Solution {
  public:
    void wiggleSort(vector<int> &nums) {
        bool inc = true;
        int sz = nums.size();
        for (int i = 0; i + 1 < sz; i++) {
            if (inc && nums[i] > nums[i + 1] || !inc && nums[i] < nums[i + 1])
                swap(nums[i], nums[i + 1]);
            inc = !inc;
        }
        return;
    }
};