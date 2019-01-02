class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> triplets;
        sort(nums.begin(), nums.end());
        int nums_sz = nums.size();
        for(int i=0; i<nums_sz;i++){
            if(i!=0 && nums[i]==nums[i-1])
                continue;
            int l=i+1, r=nums_sz-1;
            while(l<r){
                int residue = nums[i]+nums[l]+nums[r];
                if(residue==0){
                    triplets.push_back(vector<int>{nums[i],nums[l],nums[r]});
                    do{
                        l++;
                    }while(l<r && nums[l]==nums[l-1]);
                    do{
                        r--;
                    }while(l<r && nums[r]==nums[r+1]);
                }
                else if(residue<0){
                    do{
                        l++;
                    }while(l<r && nums[l]==nums[l-1]);
                }else{
                    do{
                        r--;
                    }while(l<r && nums[r]==nums[r+1]);
                }
            }
        }
        return triplets;
    }
};
