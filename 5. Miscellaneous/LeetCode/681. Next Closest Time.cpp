class Solution {
  public:
    string nextClosestTime(string time) {
        vector<int> curtime(4, 0);
        curtime[0] = time[0] - '0';
        curtime[1] = time[1] - '0';
        curtime[2] = time[3] - '0';
        curtime[3] = time[4] - '0';
        vector<int> nums;
        for (int i = 0; i < 4; i++) {
            int j = 0;
            for (j = 0; j < nums.size(); j++)
                if (nums[j] == curtime[i])
                    break;
            if (j == nums.size())
                nums.push_back(curtime[i]);
        }
        sort(nums.begin(), nums.end());
        int sz = nums.size();
        int min = nums[0], max = nums[sz - 1];
        if (min == max)
            return array2time(curtime);
        if (curtime[3] < max) {
            curtime[3] = *upper_bound(nums.begin(), nums.end(), curtime[3]);
            return array2time(curtime);
        }
        if (curtime[2] < max) {
            int nextnumber = *upper_bound(nums.begin(), nums.end(), curtime[2]);
            if (nextnumber < 6) {
                curtime[2] = nextnumber;
                curtime[3] = min;
                return array2time(curtime);
            }
        }
        if (curtime[1] < max) {
            int nextnumber = *upper_bound(nums.begin(), nums.end(), curtime[1]);
            if (nextnumber < 4 || curtime[0] < 2) {
                curtime[1] = nextnumber;
                curtime[2] = min;
                curtime[3] = min;
                return array2time(curtime);
            }
        }

        if (curtime[0] < max) {
            int nextnumber = *upper_bound(nums.begin(), nums.end(), curtime[0]);
            if (nextnumber < 2 || nextnumber == 2 && curtime[1] < 4) {
                curtime[1] = min;
                curtime[2] = min;
                curtime[3] = min;
                curtime[0] = nextnumber;
                return array2time(curtime);
            }
        }

        for (int i = 0; i < 4; i++)
            curtime[i] = min;
        return array2time(curtime);
    }

    string array2time(const vector<int> &curtime) {
        return to_string(curtime[0]) + to_string(curtime[1]) + ":" +
               to_string(curtime[2]) + to_string(curtime[3]);
    }
};