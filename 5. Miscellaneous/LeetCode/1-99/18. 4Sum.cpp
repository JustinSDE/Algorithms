class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        int sz=nums.size();
        for(int i=0; i<sz;i++){
            if(i>0 && nums[i]==nums[i-1])
                continue;
            int target_3=target-nums[i];
            for(int j=i+1; j<sz; j++){
                if(j>i+1 && nums[j]==nums[j-1])
                    continue;
                int target_2=target_3-nums[j];
                int leftIndex=j+1, rightIndex=sz-1;
                while(leftIndex<rightIndex){
                    int sum_2=nums[leftIndex]+nums[rightIndex];
                    if(sum_2==target_2){
                        res.push_back(vector<int>{nums[i], nums[j], nums[leftIndex], nums[rightIndex]});
                        while(leftIndex<rightIndex && nums[leftIndex]==nums[leftIndex+1]) leftIndex++;
                        while(leftIndex<rightIndex && nums[rightIndex]== nums[rightIndex-1]) rightIndex--;
                        leftIndex++;
                        rightIndex--;
                    }
                    else if(sum_2<target_2){
                        while(leftIndex<rightIndex && nums[leftIndex]==nums[leftIndex+1]) leftIndex++;
                        leftIndex++;
                    }
                    else{
                        while(leftIndex<rightIndex && nums[rightIndex]== nums[rightIndex-1]) rightIndex--;
                        rightIndex--;
                    } 
                }
            }
        }
        return res;
    }
};
