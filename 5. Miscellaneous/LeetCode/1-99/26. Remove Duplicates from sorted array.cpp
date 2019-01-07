class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int sz = nums.size();
        if(sz<=1){
            return sz;
        }
        int non_duplicateIndex=0;
        for(int i=1; i<sz;i++){
            if(nums[i]!=nums[non_duplicateIndex]){
                non_duplicateIndex++;
                nums[non_duplicateIndex]=nums[i];
            }
        }
        return non_duplicateIndex+1;
    }
};
