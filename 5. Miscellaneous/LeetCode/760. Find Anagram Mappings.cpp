class Solution {
  public:
    vector<int> anagramMappings(vector<int> &B, vector<int> &A) {
        unordered_map<int, vector<int>> index;
        for (int i = 0; i < A.size(); i++) {
            index[A[i]].push_back(i);
        }
        vector<int> res;
        for (auto x : B) {
            int a = index[x].back();
            index[x].pop_back();
            res.push_back(a);
        }
        return res;
    }
};