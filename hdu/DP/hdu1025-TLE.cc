/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1025
 * DP. TLE?? Oh my...
 */
#include <cstdio>
#include <cstring>

static int const MAX_CITY = 500005;
static int pair[MAX_CITY], dp[MAX_CITY];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, cases = 0;
    while (scanf("%d", &N) != EOF) {
        int poor, rich;
        memset(pair, 0, sizeof(pair));
        for (int i = 1; i <= N; ++i) {
            scanf("%d %d", &poor, &rich);
            pair[rich] = poor;
        }
        memset(dp, 0, sizeof(dp));
        // i, current rich country
        // j, previous rich country
        int result = 0, temp;
        for (int i = 1, j; i <= N; ++i) { // loop for each rich country
            j = i - 1, temp = 0;
            while (j >= 0) {
                if (pair[j] < pair[i] && temp < dp[j] + 1) {
                    temp = dp[j] + 1;
                }
                --j;
            }
            dp[i] = temp;
            result = max(result, dp[i]);
        }
        if (dp[N] > 1) {
            printf("Case %d:\nMy king, at most %d roads can be built.\n\n",
                    ++cases, result);
        } else {
            printf("Case %d:\nMy king, at most %d road can be built.\n\n",
                    ++cases, result);
        }
    }
    return 0;
}

