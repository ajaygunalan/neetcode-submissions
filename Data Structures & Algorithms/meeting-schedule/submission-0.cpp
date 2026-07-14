/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        // sort the intervals based on start value
        std::sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b){return a.start < b.start;});

        //loop all the intervals
        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i].start < intervals[i-1].end)
                return false;
        }
        return true;
    }
};
