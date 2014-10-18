#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

/**
 * Definition for an interval.
 */
struct Interval {
    int start;
    int end;
    Interval() :
        start(0), end(0) {
    }
    Interval(int s, int e) :
        start(s), end(e) {
    }
};

inline bool intervalCompare(const Interval& lhs, const Interval& rhs) {
    if (lhs.start != rhs.start) {
        return lhs.start < rhs.start;
    }
    return lhs.end < rhs.end;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        std::sort(intervals.begin(), intervals.end(), intervalCompare);
        vector<Interval> result;
        int size = intervals.size();
        int i = 0, j;
        while (i < size) {
            Interval curr = intervals[i];
            for (j = i + 1; j < size; ++j) {
                if (curr.end < intervals[j].start) {
                    break;
                } else {
                    curr.end = std::max(curr.end, intervals[j].end);
                }
            }
            i = j;
            result.push_back(curr);
        }
        return result;
    }
};

Solution solu;

int main() {

    vector<Interval> intervals, merged;
    intervals.push_back(Interval(1, 3)), intervals.push_back(Interval(2, 6));
    intervals.push_back(Interval(8, 10)), intervals.push_back(Interval(15, 18));

    merged = solu.merge(intervals);
    for (int i = 0; i < merged.size(); ++i) {
        std::cout << merged[i].start << ' ' << merged[i].end << std::endl;
    }
    std::cout << std::endl;

    intervals.clear();
    intervals.push_back(Interval(1, 3)), intervals.push_back(Interval(2, 6));
    intervals.push_back(Interval(6, 12)), intervals.push_back(Interval(8, 10));
    intervals.push_back(Interval(8, 10)), intervals.push_back(Interval(15, 18));

    merged = solu.merge(intervals);
    for (int i = 0; i < merged.size(); ++i) {
        std::cout << merged[i].start << ' ' << merged[i].end << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

