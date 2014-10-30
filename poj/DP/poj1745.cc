/**
 * http://poj.org/problem?id=1745
 *
 * Divisibility
 *
 * DP. Packing problem
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_ELEM = 10001,
    MAX_MOD = 101
};

int N, K;
int arr[MAX_ELEM];
bool dp[MAX_ELEM][MAX_MOD];

inline int mod(int a) {
    return a > 0 ? a % K : (-a) % K;
}

int main() {
    while (scanf("%d %d", &N, &K) != EOF) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }

        memset(dp, false, sizeof(dp));
        // DP[i][j] records the possibility of using the first i numbers to reach j
        dp[1][mod(arr[1])] = true;
        for (int i = 2; i <= N; ++i) {
            for (int j = K; j >= 0; --j) {
                if (dp[i - 1][j]) {
                    dp[i][mod(j - arr[i])] = dp[i][mod(j + arr[i])] = true;
                }
            }
        }

        if (dp[N][0]) {
            printf("Divisible\n");
        } else {
            printf("Not divisible\n");
        }
    }
    return 0;
}

