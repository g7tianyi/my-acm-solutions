/**
 * HDU 1176, 免费馅饼
 * http://acm.hdu.edu.cn/showproblem.php?pid=1176
 *
 * Top-Down DP will WA, still can not figure out why
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_POS = 11, MAX_PIE = 100000, MAX_TIME = 100000,
};

inline int max(int a, int b) {
    return a > b ? a : b;
}

int pie[MAX_TIME][MAX_POS];
int dp[2][MAX_POS];

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N) {
        memset(pie, 0, sizeof(pie));
        int position, time, maxTime = -1;
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &position, &time);
            maxTime = max(maxTime, time);
            ++pie[time][position];
        }

        int curr = 0, next = 1;
        memset(dp, -1, sizeof(dp));
        dp[curr][4] = pie[1][4], dp[curr][5] = pie[1][5], dp[curr][6] = pie[1][6];

        for (int i = 1; i < maxTime; ++i) {
            memset(dp[next], -1, sizeof(dp[next]));
            for (int j = 0; j <= MAX_POS; ++j) {
                if (dp[curr][j] >= 0) {
                    if (j > 0) {
                        dp[next][j - 1] = max(dp[next][j - 1], dp[curr][j] + pie[i + 1][j - 1]);
                    }
                    if (j < MAX_POS) {
                        dp[next][j + 1] = max(dp[next][j + 1],dp[curr][j] + pie[i + 1][j + 1]);
                    }
                    dp[next][j] = max(dp[next][j], dp[curr][j] + pie[i + 1][j]);
                }
            }
            curr ^= 1, next ^= 1;
        }

        int result = dp[curr][0];
        for (int j = 1; j <= MAX_POS; ++j) {
            result = max(result, dp[curr][j]);
        }
        printf("%d\n", result);
    }
    return 0;
}

