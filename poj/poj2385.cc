/**
 * POJ 2385, Apple Catching
 * DP.
 *
 * F(i,j), max apples Bessie can get in the first i intervals
 * with being switched between two trees j times
 *
 * F(i, j) = max {
 *     F(i - 1, k) + C(i, k) for k in [0, j -1]
 * }
 * C(i, k) is the apples in interval i when switched k times
 */
#include <cstdio>

#define MAX(a, b) (a) > (b) ? (a) : (b)

int dp[31];

int main() {
    int T, W, tree;
    scanf("%d %d", &T, &W);
    while (T--) {
        scanf("%d", &tree);
        if (tree == 1) {
            for (int i = 2; i <= W; i += 2) {
                dp[i] = MAX(dp[i], dp[i - 1]) + 1;
            }
            ++dp[0];
        } else {
            for (int i = 1; i <= W; i += 2) {
                dp[i] = MAX(dp[i], dp[i - 1]) + 1;
            }
        }
    }
    printf("%d\n", MAX(dp[W], dp[W - 1]));
    return 0;
}

