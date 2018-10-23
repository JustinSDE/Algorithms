class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for(int i=0; i <nums.size();i++){
            for(int j=i+1; j<nums.size();j++){
                if(nums[i]+nums[j]==target){
                    return vector<int>{i,j};
                }
            }
        }
        return vector<int>{-1,-1};
    }
};




class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> checked;
        for(int i=0;i<nums.size();i++){
            int counter_num=target-nums[i];
            if(checked.count(counter_num)==1){
                return vector<int>{checked[counter_num],i};
            }
            checked[nums[i]]=i;
        }
        return vector<int>{-1,-1};
    }
};