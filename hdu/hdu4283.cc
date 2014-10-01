/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=4283
 * Good. Range DP.
 *
 * F(i, j), the min cost of arranging people in [i, j]
 * F(i, j) = min { F(i, j), F(i, k) + F(k + 1, j) }
 * Well, not likely this, but this is the kernel equation
 */
#include <cstdio>
#include <cstring>

const int MAX_N = 102;

inline int min(int a, int b) {
    return a < b ? a : b;
}

int value[MAX_N], sum[MAX_N];
int dp[MAX_N][MAX_N];

int main() {
    int T, N;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &N);
        sum[0] = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &value[i]);
            sum[i] = sum[i - 1] + value[i];
        }
        memset(dp, -1, sizeof(dp));

        int temp;
        for (int L = 1; L <= N - 1; L++) { // try each range length
            for (int i = 1; i <= N - L; i++) { // try the start of current range
                int j = i + L; // end of current range
                for (int k = i; k <= j; k++) { // try the order of going to stage
                    temp = value[i] * (k - i) + (k - i + 1) * (sum[j] - sum[k])
                            + dp[i + 1][k] + dp[k + 1][j];
                    if (dp[i][j] == -1 || dp[i][j] < temp)
                        dp[i][j] = temp;
                }
            }
            //printf("\n");
        }

        printf("Case #%d: %d\n", t, dp[1][N]);
    }

    return 0;
}

