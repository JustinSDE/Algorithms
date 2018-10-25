class Solution {
  public:
    vector<vector<string>> groupStrings(vector<string> &strings) {
        unordered_map<string, vector<string>> collections;
        for (auto &str : strings) {
            collections[mapping(str)].push_back(str);
        }
        vector<vector<string>> res;
        for (auto &values : collections) {
            res.push_back(move(values.second));
        }
        return res;
    }

    string mapping(string s) {
        if (s.empty())
            return "";
        if (s.length() == 1)
            return "-";
        int slength = s.length();
        string ret;
        for (int i = 0; i + 1 < slength; i++) {
            re = (s[i + 1] - s[i] + 26) % 26 + 'a';
        }
        return ret;
    }
};

// reducing copying
class Solution1 {
  public:
    vector<vector<string>> groupStrings(vector<string> &strings) {
        unordered_map<string, vector<int>> collections;
        int i = 0;
        for (auto &str : strings) {
            collections[mapping(str)].push_back(i);
            i++;
        }
        vector<vector<string>> res(collections.size());
        i = 0;
        for (auto &values : collections) {
            for (auto num : values.second)
                res[i].push_back(strings[num]);
            i++;
        }
        return res;
    }

    string mapping(string s) {
        if (s.empty())
            return "";
        if (s.length() == 1)
            return "-";
        int slength = s.length();
        string ret;
        for (int i = 0; i + 1 < slength; i++) {
            ret.push_back((s[i + 1] - s[i] + 26) % 26 + 'a');
        }
        return ret;
    }
};

// use std move to further reduce the requirement of copying the string
class Solution2 {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string,vector<int>> collections;
        int i=0;
        for(auto& str:strings){
            collections[mapping(str)].push_back(i);
            i++;
        }
        vector<vector<string>> res(collections.size());
        i=0;
        for(auto& values:collections){
            for(auto num:values.second)
                res[i].push_back(move(strings[num]));
            i++;
        }
        return res;
        
    }
    
    string mapping(string s){
        if(s.empty())
            return "";
        if(s.length()==1)
            return "-";
        int slength=s.length();
        string ret;
        for(int i=0; i+1<slength;i++){
            ret.push_back((s[i+1]-s[i]+26)%26+'a');
        }
        return ret;
    }
};

// map to index of return 2d array to further reduce time requirement
class Solution3 {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string>> ans;
        unordered_map<string, int> umap;
        for(string s: strings){
            string key="0";
            char firstLetter = s[0];
            for(int i=1; i<s.length(); i++){
                char temp = (s[i]-firstLetter+26)%26+'a';
                key+=temp;
            }
            if(umap.count(key)!=0){
                ans[umap[key]].push_back(move(s));
            }
            else{
                vector<string> n;
                n.push_back(s);
                umap[key]=ans.size();
                ans.push_back(n);
            }
        }
        return ans;
    }
};