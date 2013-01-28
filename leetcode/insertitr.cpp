/*
 * Insert Interval
 * Given a set of non-overlapping intervals, insert a new interval 
 * into the intervals (merge if necessary).
 * 
 * You may assume that the intervals were initially 
 * sorted according to their start times.
 * 
 * Example 1:
 *   Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * 
 * Example 2:
 *   Given [1,2],[3,5],[6,7],[8,10],[12,16], 
 *   insert and merge [4,9] in as [1,2],[3,10],[12,16].
 * 
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 *
 * Sol: Using two containers to hold the two parts of the vector<Interval>!
 * any thing before the newInteval are directly push_back to ret,
 * amy thing intersects or after newInterval are handled in another deque!
 */ 

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    deque<Interval> buf;
    vector<Interval> ret;
    buf.push_back(newInterval);
    
    int len = intervals.size();
    for (int i=0; i<len; i++) {
        if (intervals[i].end < buf[0].start) {
            ret.push_back(intervals[i]);
        } else if (intervals[i].start > buf.back().end) {
            buf.push_back(intervals[i]);
        } else {
            buf[0].start = min(buf[0].start, intervals[i].start);
            buf[0].end = max(buf[0].end, intervals[i].end);
        }
    }
    
    while (!buf.empty()) {
        ret.push_back(buf.front());
        buf.pop_front();
    }
    return ret;
}
