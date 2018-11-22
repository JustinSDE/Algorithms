
class Solution {
  public:
    string process_local_name(string str) {
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '.')
                str.erase(i, 1);
            if (str[i] == '+') {
                str.erase(i, str.size() - i);
                return str;
            }
        }
        return str;
    }
    int numUniqueEmails(vector<string> &emails) {
        unordered_set<string> map;
        int count = 0;
        for (int j = 0; j < emails.size(); j++) {
            // find index of @:
            int index = 0;
            string temp = emails[j];
            for (int i = 0; i < temp.size(); i++)
                if (temp[i] == '@') {
                    index = i;
                    break;
                }
            // local name:
            temp = process_local_name(temp.substr(0, index));
            // process domain name:
            string tmp = temp + emails[j].substr(index + 1, emails[j].size());
            if (map.count(tmp) == 0) {
                map.insert(tmp);
                count++;
            }
        }
        return count;
    }
};