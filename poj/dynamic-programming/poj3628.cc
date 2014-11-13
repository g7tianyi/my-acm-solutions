/**
 * http://poj.org/problem?id=3628
 *
 * Bookshelf 2
 *
 * DP. 0-1 packing problem
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_HEIGHT = 1000003 << 1,
    MAX_COW = 22
};

int N, S;
int height[MAX_COW];
int dp[MAX_HEIGHT];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    while (scanf("%d %d", &N, &S) != EOF) {
        int total = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &height[i]);
            total += height[i];
        }

        memset(dp, 0, sizeof(dp));
        // dp[i][j], max height (no taller than j) can be reached with the first i cows
        // 0-1 packing problem.
        // dp[i][j] = max { dp[i-1][j], dp[i-1][j - height[i]] + height[i] }
        // means either we do not use cow i, so the problem becomes the maximum of the
        // previous i - 1 cows, or we use cow i, then the problem becomes the maximum
        // of the previous i - 1 cows with "height" (capacity) j - height[i]
        for (int i = 1; i <= N; ++i) {
            for (int j = total; j >= height[i]; --j) {
                dp[j] = max(dp[j], dp[j - height[i]] + height[i]);
            }
        }

        for (int i = S; i <= total; ++i) {
            if (i == dp[i]) {
                printf("%d\n", dp[i] - S);
                break;
            }
        }
    }
    return 0;
}

