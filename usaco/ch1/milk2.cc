/*
 ID: fairyroad1106
 PROG: milk2
 LANG: C++
 */
#include <cstdio>
#include <algorithm>

#define PROGID "milk2"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int MAX_FARMER = 5005;

struct RANGE {
    int start, end;
    RANGE() : start(0), end(0) {}
};

inline bool operator<(const RANGE& lhs, const RANGE& rhs) {
    if (lhs.start != rhs.start) {
        return lhs.start < rhs.start;
    }
    return lhs.end < rhs.end;
}

RANGE ranges[MAX_FARMER];

// DP
int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &ranges[i].start, &ranges[i].end);
    }
    std::sort(ranges, ranges + N);

    // can be seen as a maximum continuous subarray
    // F(i) the range end for the first i farmers
    // F(i) = {
    //     max(range[i], F(i-1)), if range[i].start < F(i-1)
    //     range[i].end, otherwise
    // }
    int max_busy = -1, max_idle = -1;
    int prev_start = ranges[0].start;
    int prev_end = ranges[0].end;
    for (int i = 1; i < N; ++i) {
        if (ranges[i].start <= prev_end) { // overlapped
            prev_end = MAX(prev_end, ranges[i].end);
        } else {
            if (max_idle < ranges[i].start - prev_end) {
                max_idle = ranges[i].start - prev_end;
            }
            if (max_busy < prev_end - prev_start) {
                max_busy = prev_end - prev_start;
            }
            prev_start = ranges[i].start;
            prev_end = ranges[i].end;
        }
    }

    printf("%d %d\n", max_busy, max_idle);

    return 0;
}

