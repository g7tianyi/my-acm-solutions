#include <algorithm>
#include <iostream>

#include <string>
using std::string;

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

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> result;
        result.push_back(newInterval);
        for (int i = 0; i < intervals.size(); i++) {
            Interval next = result.back();
            result.pop_back();
            Interval curr = intervals[i];
            if (curr.end < next.start) {
                result.push_back(curr);
                result.push_back(next);
            } else if (curr.start > next.end) {
                result.push_back(next);
                result.push_back(curr);
            } else {
                next.start = std::min(curr.start, next.start);
                next.end = std::max(curr.end, next.end);
                result.push_back(next);
            }
        }
        return result;
    }
};

Solution solu;
vector<Interval> intervals;

void init() {
    intervals.clear();
    intervals.push_back(Interval(1, 2));
    intervals.push_back(Interval(3, 5));
    intervals.push_back(Interval(6, 7));
    intervals.push_back(Interval(8, 10));
    intervals.push_back(Interval(12, 16));
}

void print(vector<Interval>& newIntervals) {
    for (int i = 0; i < newIntervals.size(); ++i) {
        std::cout << newIntervals[i].start << ' ' << newIntervals[i].end << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    vector<Interval> newIntervals;

    intervals.clear();
    intervals.push_back(Interval(1, 3));
    intervals.push_back(Interval(6, 9));
    newIntervals = solu.insert(intervals, Interval(2, 5));
    print(newIntervals);

    intervals.clear();
    intervals.push_back(Interval(1, 3));
    newIntervals = solu.insert(intervals, Interval(2, 5));
    print(newIntervals);

    intervals.clear();
    intervals.push_back(Interval(1, 3));
    newIntervals = solu.insert(intervals, Interval(1, 4));
    print(newIntervals);

    intervals.clear();
    intervals.push_back(Interval(1, 3));
    newIntervals = solu.insert(intervals, Interval(4, 5));
    print(newIntervals);

    intervals.clear();
    intervals.push_back(Interval(23, 45));
    intervals.push_back(Interval(100, 200));
    newIntervals = solu.insert(intervals, Interval(1, 2));
    print(newIntervals);

    intervals.clear();
    intervals.push_back(Interval(1, 2));
    intervals.push_back(Interval(100, 200));
    newIntervals = solu.insert(intervals, Interval(60, 70));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(4, 9));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(3, 10));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(3, 11));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(3, 12));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(5, 10));
    print(newIntervals);

    init();
    newIntervals = solu.insert(intervals, Interval(5, 12));
    print(newIntervals);

    return 0;
}

