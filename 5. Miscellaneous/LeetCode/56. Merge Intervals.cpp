/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
  public:
    vector<Interval> merge(vector<Interval> &intervals) {
        vector<Interval> res;
        sort(intervals.begin(), intervals.end(),
             [](const Interval &a, const Interval &b) {
                 return a.start < b.start;
             });
        if (intervals.empty())
            return res;
        int cur = 0;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (res[cur].end >= intervals[i].start)
                res[cur].end = max(res[cur].end, intervals[i].end);
            else {
                res.push_back(intervals[i]);
                cur++;
            }
        }
        return res;
    }
};