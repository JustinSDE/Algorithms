class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        permuteHelper(nums, 0, res);
        return res;
    }
    
    void permuteHelper(vector<int>& candidate, int index, vector<vector<int>>& permutations){
        int sz = candidate.size();
        if(index == sz){
            permutations.push_back(candidate);
            return;
        }
        for(int i=index; i<sz; i++){
            swap(candidate[i],candidate[index]);
            permuteHelper(candidate, index+1, permutations);
            swap(candidate[i], candidate[index]);
        }
        return;
    }
};
