class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int error=INT_MAX;
        int res;
        int sz=nums.size();
        for(int i=0; i<sz;i++){
            if(i>0 && nums[i]==nums[i-1])
                continue;
            int target_2=target-nums[i];
            int leftIndex=i+1, rightIndex=sz-1;
            while(leftIndex<rightIndex){
                int curError=nums[leftIndex]+nums[rightIndex]-target_2;
                if(curError==0){
                    return target;
                }
                if(abs(curError)<error){
                    error=abs(curError);
                    res=nums[i]+nums[leftIndex]+nums[rightIndex];
                }
                if(curError>0){
                    while(rightIndex>leftIndex && nums[rightIndex-1]==nums[rightIndex])
                        rightIndex--;
                    rightIndex--;
                }
                else{
                    while(leftIndex<rightIndex && nums[leftIndex+1]==nums[leftIndex])
                        leftIndex++;
                    leftIndex++;
                }
            }
        }
        return res;
    }
};
