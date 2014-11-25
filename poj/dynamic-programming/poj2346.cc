/**
 * http://poj.org/problem?id=2346
 *
 * simple dynamic programming. 0-1 packing
 */

#include <iostream>

int dp[5 * 9 + 1];

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int num;
    scanf("%d", &num);

    num >>= 1;
    memset(dp, 0, sizeof(dp));
    // dp[i][j], use i digits to get sum j
    // dp[i][j] = sum { dp[i-1][j-k] | k in [0, 9] }
    dp[0] = 1;
    for (int i = 1; i <= num; ++i) {
        for (int j = 45; j >= 0; --j) {
            for (int k = 1; k < min(10, j + 1); ++k) {
                // append a digit k
                dp[j] += dp[j - k];
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= 45; ++i) {
        result += dp[i] * dp[i];
    }
    printf("%d\n", result);

    return 0;
}

