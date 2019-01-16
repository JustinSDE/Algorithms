class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int stepSum=0, res=INT_MIN;
        for(int i=0;i<nums.size();i++){
            stepSum+=nums[i];
            if(stepSum>res){
                res=stepSum;
            }
            if(stepSum<0){
                stepSum=0;
            }
        }
        return res;
        
    }
};
