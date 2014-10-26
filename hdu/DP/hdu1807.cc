/**
 * HDU 1807, Super Jumping! Jumping! Jumping!
 * http://acm.hdu.edu.cn/showproblem.php?pid=1087
 * DP, maximum increasing subarray. Good problem.
 *
 * F(i), max sum of increasing subsarray ending in i
 * F(i) = max { F(j) + V(j), where j in [0, i) and V(j) < V(i) }
 */
#include <cstdio>
#include <cstring>

inline int max(int a, int b) {
    return a > b ? a : b;
}
const int MAX_CHESSMEN = 1002;
int chess[MAX_CHESSMEN], dp[MAX_CHESSMEN];

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &chess[i]);
            dp[i] = chess[i];
        }
        int result = dp[0];
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (chess[i] > chess[j]) {
                    dp[i] = max(dp[i], dp[j] + chess[i]);
                }
            }
            result = max(result, dp[i]);
        }
        printf("%d\n", result);
    }
    return 0;
}

