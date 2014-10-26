/**
 * POJ 1952, BUY LOW, BUY LOWER
 * DP
 * F(i) is the longest decreasing sequence ending in i
 * F(i) = max { 1, max { F(j) + 1 | j in [0, i) and S(j) > S(i) } }
 */
#include <cstdio>
#include <cstring>

#define MAX(a, b) (a) > (b) ? (a) : (b)

struct state {
    int maxlen, count;
};

const int MAX_DAYS = 5001;
int stocks[MAX_DAYS];
state dp[MAX_DAYS];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &stocks[i]);
    }
    for (int i = 0; i < N; ++i) {
        dp[i].count = dp[i].maxlen = 1;
    }

    int maxlen = 1, count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (stocks[j] > stocks[i]) {
                if (dp[i].maxlen < dp[j].maxlen + 1) {
                    dp[i].maxlen = dp[j].maxlen + 1;
                    dp[i].count = dp[j].count;
                    maxlen = MAX(maxlen, dp[i].maxlen);
                } else if (dp[i].maxlen == dp[j].maxlen + 1) {
                    dp[i].count += dp[j].count;
                }
            } else if (stocks[j] == stocks[i]) {
                // if the prices are the same,
                // do not count the solutions based on stock k
                if (dp[i].maxlen == 1) {
                    dp[i].count = 0;
                }
                break;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (dp[i].maxlen == maxlen) {
            count += dp[i].count;
        }
    }
    printf("%d %d\n", maxlen, count);
    return 0;
}

