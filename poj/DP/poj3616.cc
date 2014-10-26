/**
 * POJ 3616, Milking Time
 * DP.
 *
 * Another solution is, extends every interval's ending time with R,
 * then the problem can be seen as getting the maximum summary of all
 * non-overrlapping intervals => smells like the LIS problem..
 */
#include <cstdio>
#include <algorithm>

enum {
    MAX_HOUR = 1000001, MAX_INTERVAL = 1001,
};

struct INTERVAL {
    int start, end, efficiency;
};

inline bool operator<(const INTERVAL& lhs, const INTERVAL& rhs) {
    if (lhs.start != rhs.start) {
        return lhs.start < rhs.start;
    }
    return lhs.end < rhs.end;
}

INTERVAL intervals[MAX_INTERVAL];
int dp[MAX_INTERVAL];

int main() {

    int N, M, R; // number of hours, intervals and rest time
    scanf("%d %d %d", &N, &M, &R);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &intervals[i].start, &intervals[i].end,
                &intervals[i].efficiency);
    }

    std::sort(intervals, intervals + M);
    int i, j, result = -1;
    for (i = 0; i < M; ++i) { // try all intervals as the current ending interval
        dp[i] = intervals[i].efficiency;
        for (j = i - 1; j >= 0; --j) { // try all previous intervals as the direct predecessor
            if (intervals[i].start - intervals[j].end >= R
                    && dp[i] < dp[j] + intervals[i].efficiency) {
                dp[i] = dp[j] + intervals[i].efficiency;
            }
        }
        if (result < dp[i]) {
            result = dp[i];
        }
    }
    printf("%d\n", result);

    return 0;
}

