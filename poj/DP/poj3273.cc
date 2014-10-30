/**
 * http://poj.org/problem?id=3273
 *
 * Monthly Expense
 *
 * Greedy algo, binary search
 */

#include <cstdio>

int const MAX_DAYS = 100002;
int value[MAX_DAYS];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M; // N days, M sections
    scanf("%d %d", &N, &M);

    int maxcost = -1, sumcost = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &value[i]);
        maxcost = max(maxcost, value[i]);
        sumcost += value[i];
    }

    int first = maxcost, last = sumcost, mid;
    while (first < last) {
        mid = first + ((last - first) >> 1);
        int count = 1, range = 0; // sum of values in a range
        for (int i = 0; i < N; ++i) {
            range += value[i];
            if (range > mid) {
                ++count;
                range = value[i];
            }
        }
        if (count > M) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    printf("%d\n", last);

    return 0;
}

