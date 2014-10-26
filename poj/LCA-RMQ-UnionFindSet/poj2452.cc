/**
 * http://poj.org/problem?id=2452
 * Sticks Problem
 *
 * RMQ problems => DP
 */
#include <iostream>

const int MAX_STICK = 50005;

int sticks[MAX_STICK];

enum QueryType {
    QUERY_MAX, QUERY_MIN
};

struct RMQ {
    inline void init(int size) {
        for (int i = 1; i <= size; ++i) {
            // start from range i with length 0
            // the max/min value of course is itself
            maxValue[i][0] = minValue[i][0] = i;
        }

        int k = log(size);
        for (int j = 1; j <= k; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= size; ++i) {
                minValue[i][j] = myMin(minValue[i][j - 1],
                        minValue[i + (1 << (j - 1))][j - 1]);
                maxValue[i][j] = myMax(maxValue[i][j - 1],
                        maxValue[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int first, int last, QueryType queryType) {
        int k = log(last - first + 1);
        if (queryType == QUERY_MAX) {
            return myMax(maxValue[first][k], maxValue[last - (1 << k) + 1][k]);
        } else {
            return myMin(minValue[first][k], minValue[last - (1 << k) + 1][k]);
        }
    }
private:
    inline int log(int n) {
        int k = 0;
        while (n) {
            ++k;
            n >>= 1;
        }
        return k - 1;
    }
    inline int myMax(int a, int b) {
        return sticks[a] > sticks[b] ? a : b;
    }
    inline int myMin(int a, int b) {
        return sticks[a] < sticks[b] ? a : b;
    }
private:
    int maxValue[MAX_STICK][20];
    int minValue[MAX_STICK][20];
};

static RMQ rmq;

int query_range(int curr) {
    int first = 1, last = curr - 1, mid;
    int index = -1;
    while (first <= last) {
        mid = first + ((last - first) >> 1);
        // query the index of the max value in [mid, curr - 1]
        int maxi = rmq.query(mid, curr - 1, QUERY_MAX);
        if (sticks[maxi] > sticks[curr]) {
            // have to move forward
            // drop range  [first, mid] since sticks[maxi] stands in the way of curr
            first = mid + 1;
        } else {
            // could move backward
            // drop range [mid, last] since they all smaller than sticks[curr]
            last = mid - 1;
            index = mid;
        }
    }
    if (index == -1) {
        return curr + 1;
    } else {
        return rmq.query(index, curr - 1, QUERY_MIN);
    }
}

int main() {
    int numStick;
    while (scanf("%d", &numStick) != EOF) {
        for (int i = 1; i <= numStick; ++i) {
            scanf("%d", &sticks[i]);
        }
        rmq.init(numStick);
        int result = -1, start;
        for (int i = numStick; i > 0; --i) {
            start = query_range(i);
            if (result < i - start) {
                result = i - start;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}

