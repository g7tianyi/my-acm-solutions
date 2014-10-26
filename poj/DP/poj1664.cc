/**
 * POJ 1664
 * 3-d DP
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_APPLE = 16,
    MAX_PANEL = 16
};

int dp[MAX_APPLE][MAX_PANEL][MAX_APPLE];

int main() {
    int T, M, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &M, &N);
        // F(i,j,k), solutions of putting i appels into j panels
        // with each panel contains at least k apples
        // F(i,j,k) = sum { F(i-m, j-1, m) | m in [k, i] }
        // means when we put m apples in panel i
        // the whole solutions rely on the arrangement of
        // the rest (i-m) appels into j-1 panels
        memset(dp, 0, sizeof(dp));
        int i, j, k, m;
        for (i = 1; i <= M; ++i) {
            for (k = 0; k <= i; ++k) {
                // put i apples into 1 panel while each
                // panel contains at least k apples
                dp[i][1][k] = 1;
            }
        }

        for (i = 1; i <= M; ++i) { // looping apples
            for (j = 1; j <= N; ++j) { // looping panels
                for (k = 0; k <= i; ++k) { // apples in panel-j
                    for (m = k; m <= i; ++m) { // minimum apples in the rest j-1 panels
                        dp[i][j][k] += dp[i - m][j - 1][m];
                    }
                    //printf("dp[%d][%d][%d] <- %d\n", i, j, k, dp[i][j][k]);
                }
            }
        }

        printf("%d\n", dp[M][N][0]);
    }
    return 0;
}

