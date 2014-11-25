/**
 * http://poj.org/problem?id=3624
 * Charm Bracelet
 *
 * dynamic programming. 0-1 packing problem.
 */

#include <iostream>

int weigh[3420], value[3420];
int dp[12890];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &weigh[i], &value[i]);
    }

    // dp[i][j], maximum desirability of weight j using the former i charms
    // dp[i][j] = max { dp[i][j], dp[i - 1][j - W[i]] + V[i] }
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < N; ++i) {
        for (int j = M; j >= weigh[i]; --j) {
            if (dp[j] < dp[j - weigh[i]] + value[i]) {
                dp[j] = dp[j - weigh[i]] + value[i];
            }
        }
    }
    printf("%d\n", dp[M]);

    return 0;
}

