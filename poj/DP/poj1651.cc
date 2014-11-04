/**
 * http://poj.org/problem?id=1651
 *
 * Multiplication Puzzle
 *
 * DP classical problem
 */

#include <cstdio>

enum {
    MAX_CARD = 101,
    MAX_INF  = 1 << 24 // dimension range from 1 to 100 (1 << 7)
};

inline int min(int a, int b) {
    return a < b ? a : b;
}

int dim[MAX_CARD]; // dimension
int dp[MAX_CARD][MAX_CARD];

int main() {
    int len;
    scanf("%d", &len);
    for (int i = 1; i <= len; ++i) {
        scanf("%d", &dim[i - 1]);
        dp[i][i] = 0;
    }

    // we see the problem as a matrix-chain multiplication problem
    // e.g., for 10 1 50 50 20 5
    // the matrixs is
    // 10 * 1, 1 * 50, 50 * 50, 50 * 20, 20 * 5
    //
    // dp[i][j] is the minimum multiplication operation needed for matrixs in [i, j]
    // dp[i][j] = 0 if i == j
    // dp[i][j] = min(dp[i][k] + dp[k + 1][j] + dim[i - 1] * dim[k] * dim[j]), k in [i, j)
    //
    // the rest is just being careful of identify the dimensions of each matrix
    --len;
    for (int l = 2; l <= len; ++l) { // length
        for (int i = 1; i + l - 1 <= len; ++i) { // start
            int j = i + l - 1; // end
            dp[i][j] = MAX_INF;
            for (int k = i; k < j; ++k) {
                dp[i][j] = min(dp[i][j],
                        dp[i][k] + dp[k + 1][j] + dim[i - 1] * dim[k] * dim[j]);
            }
        }
    }

    printf("%d\n", dp[1][len]);
    return 0;
}

