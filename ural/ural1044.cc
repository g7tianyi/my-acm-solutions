/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1044
 */
#include <cstdio>
#include <cstring>

const static int MAX_SUM = 4 * 9 + 1;
static int dp[MAX_SUM];

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    N >>= 1;
    // F(i, j), i digits to get sum j
    // F(i, j) = sum { F(i - 1, j - k) | k in [0, 9] }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 36; j >= 0; --j) {
            for (int k = 1; k < min(10, j + 1); ++k) {
                dp[j] += dp[j - k];
            }
            //printf("dp[%d][%d]=%d\t", i, j, dp[j]);
        }
        //printf("\n");
    }
    int result = 0;
    for (int i = 0; i <= 36; ++i) {
        result += dp[i] * dp[i];
    }
    printf("%d\n", result);
    return 0;
}

