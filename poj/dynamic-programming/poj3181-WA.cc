/**
 * http://poj.org/problem?id=3181
 *
 * dynamic programming. 0-1 packing.
 * need high precision addition.
 */

#include <iostream>

typedef unsigned long long ullong;
ullong dp[1005];

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= N; ++i) {
        dp[i] = 1;
    }

    for (int i = 2; i <= K; ++i) { // loop the value of the coin
        for (int j = N; j >= i; --j) { // the sum of values
            for (int k = 1; k * i <= j; ++k) {
                // k is the count of coins i being picked
                dp[j] += dp[j - k * i];
            }
        }
    }
    printf("%llu\n", dp[N]);

    return 0;
}

