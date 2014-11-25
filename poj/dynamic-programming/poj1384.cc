/**
 * http://poj.org/problem?id=1384
 *
 * dynamic programming. packing problem.
 *
 * in this problem the knapsack must be absolutely filled in,
 * must be initialized with MAX_INF
 */

#include <iostream>

const int MAX_INF = 2000000000;

// 7000 = 500 * 14
// 14 comes from 1 << 14 = 16384 > 10000
int weigh[7000], value[7000];
int dp[10002];

int main() {
    // T test cases
    // E weight of an empty pig
    // F weight of the pig filled with coins
    // N number of various coins used in the given currency
    int T, E, F, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &E, &F, &N);
        int weight = F - E, count = 0;
        for (int i = 0, V, W; i < N; ++i) {
            scanf("%d %d", &V, &W);
            int K = 1;
            while (W * K < weight) {
                value[count] = V * K;
                weigh[count] = W * K;
                K <<= 1;
                ++count;
            }
            value[count] = (weight / W) * V;
            weigh[count] = (weight / W) * W;
            ++count;
        }

        // dp[i][j] is the minimum values of filling a pig of
        // capacity j by the former i coins
        // dp[i][j] = min { dp[i][j], dp[i-1][j-W(i)] + V(i) }
        for (int j = 1; j <= weight; ++j) {
            dp[j] = MAX_INF;
        }

        for (int i = 0; i < count; ++i) {
            for (int j = weight; j >= weigh[i]; --j) {
                if (dp[j - weigh[i]] != MAX_INF
                        && dp[j] > dp[j - weigh[i]] + value[i]) {
                    dp[j] = dp[j - weigh[i]] + value[i];
                }
            }
        }

        if (dp[weight] != MAX_INF) {
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[weight]);
        } else {
            printf("This is impossible.\n");
        }
    }
    return 0;
}

