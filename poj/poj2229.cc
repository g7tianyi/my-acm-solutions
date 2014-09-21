/**
 * POJ 2229, Sumsets
 * DP.
 *
 * F(i), arrangement count for number i
 * F(i) = {
 *    F(i-1) if i is an odd number,
 *    F(i/2) + F (i - 2) otherwise
 * }
 * 1) odd number: 7 = 6 + 1, other than that, we have no other arrangement.
 * 2) even number: 10,
 *      A) for an arrangement of 5, say, 2 1 1 1, multiply 2 for each element,
 *         we get 4 2 2 2, this's the case we have no 1 in the arrangement
 *      B) for an arrangement of 8, say 4 2 2, append two 1s to the rear,
 *         we get 4 2 2 1 1, the case which has 1 in the arrangement
 *
 * Another choice is,
 * Let F(i, j) represents the count of arrangement for num i with the maximum
 * factor not greater than j, j must be power of 2
 * F(i, j) = F(i - k, k)
 * means we firstly place k in the first place, the solution count relies on the
 * arrangement of (i - k).
 * restriction to j's maximum value aims to avoid repeated arrangement.
 *
 * e.g., 7
 *   1) 4 + F(3, 4) => 4 2 1, 4 1 1 1
 *   2) 2 + F(5, 2) => 2 2 2 1, 2 2 1 1 1, 2 1 1 1 1 1
 *   3) 1 + F(6, 1) => 1 1 1 1 1 1 1
 */
#include <cstdio>

enum {
    MAX_NUM = 1000001,
    MODULAR = 1000000000
};

int dp[MAX_NUM];

int main() {
    int N;
    scanf("%d", &N);

    dp[0] = dp[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (i & 0x1u) {
            dp[i] = dp[i - 1];
        } else {
            dp[i] = (dp[i - 2] + dp[i >> 1]) % MODULAR;
        }
    }
    printf("%d\n", dp[N]);
    return 0;
}

