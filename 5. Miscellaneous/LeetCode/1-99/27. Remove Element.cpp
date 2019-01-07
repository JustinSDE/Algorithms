class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty())
            return 0;
        int left = 0, right = nums.size() - 1;
        while(left<right){
            if (nums[left] != val) {
                left++;
                continue;
            }
            while (nums[right] == val && right > left) {
                right--;
            }
            swap(nums[left], nums[right--]);
        }
        return nums[left] == val ? left : left + 1;
    }
};

class Solution2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int index=0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]!=val)
            {
                swap(nums[i],nums[index]);
                index++;
            }
            
        }
        return index;
    }
};