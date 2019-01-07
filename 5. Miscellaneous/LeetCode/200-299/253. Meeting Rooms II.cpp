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
    int minMeetingRooms(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(),
             [](Interval &a, Interval &b) { return a.start < b.start; });
        vector<int> rooms;
        for (auto meeting : intervals) {
            bool find = false;
            for (auto &room : rooms) {
                if (room <= meeting.start) {
                    find = true;
                    room = meeting.end;
                    break;
                }
            }
            if (!find) {
                rooms.push_back(meeting.end);
            }
        }
        return rooms.size();
    }
};