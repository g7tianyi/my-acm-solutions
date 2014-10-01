/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1009
 * K-based Numbers. DP.
 *
 * F(i, j), j in [0, 1], is the possible solutions of placing j in
 * position i. j equals 0 means placing 0 in i, 1 means placing
 * non-zero numbers in i, hence,
 *    F(1, 0) = 0, F(1, 1) = K - 1
 *    F(i, 0) = F(i - 1, 1)
 *    F(i, 1) = (K - 1) * (F(i - 1, 1) + F(i - 1, 0))
 */
#include <cstdio>
#include <cstring>

typedef long long LONG;

LONG dp[24][2];

int main() {
    int N, K;
    while (scanf("%d %d", &N, &K) != EOF) {
        dp[1][0] = 0, dp[1][1] = K - 1;
        for (int i = 2; i <= N; ++i) {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = (K - 1) * (dp[i - 1][1] + dp[i - 1][0]);
        }
        printf("%lld\n", dp[N][0] + dp[N][1]);
    }
    return 0;
}

