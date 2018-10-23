class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mp;
        vector<vector<string>> res;
        int i=0;
        for(auto s:strs)
        {
            sort(s.begin(),s.end());
            mp[s].push_back(strs[i++]);
        }
        for(auto m:mp)
        {
            res.push_back(move(m.second));
        }
        return res;
            
    }
};