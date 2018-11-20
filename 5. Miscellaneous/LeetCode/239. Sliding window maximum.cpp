class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> res;
        deque<int> interdata;
        for (int i = 0; i < nums.size(); i++) {
            if (!interdata.empty() && interdata.back() == i - k)
                interdata.pop_back();
            while (!interdata.empty() && nums[interdata.front()] <= nums[i])
                interdata.pop_front();
            interdata.push_front(i);
            if (i >= k - 1)
                res.push_back(nums[interdata.back()]);
        }
        return res;
    }
};