/**
 * POJ 1953, World Cup Noise
 * DP.
 *
 * F(i,j), solution count when arranging the first i elements with the
 * i-th element being  j. j can only be 0 or 1.
 *
 * F(i, j) = {
 *     j = 1, F(i - 1, 0)
 *     j = 0, F(i - 1, 0) + F(i - 1, 1)
 * }
 * But no need to do that, we can simplify it to
 * F(i) = F(i - 1) + F(i - 2)
 */
#include <cstdio>

typedef long long MYLONG;

const int MAX_N = 50;
MYLONG dp[MAX_N];

int main() {
    dp[0] = 1, dp[1] = 2;
    for (int i = 2; i < MAX_N; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int T, N;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &N);
        printf("Scenario #%d:\n", i);
        printf("%lld\n\n", dp[N]);
    }

    return 0;
}

