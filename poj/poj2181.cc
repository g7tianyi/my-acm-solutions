/**
 * POJ 2181, Jumping Cows
 * 0-1 packing problem, or, max subarray
 *
 * F(i, S), maximum ending in potion i with state S (odd, even)
 * F(i, S) = max {
 *     F(i-1, ~S) + P(i) if S is odd,
 *     F(i-1, ~S) - P(i) if S is even
 * }
 */
#include <cstdio>

const int MAX_POTION = 150001;
enum ORDER {
    ODD = 0, EVEN = 1
};
int potion[MAX_POTION];
int dp[2][2];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int P;
    scanf("%d", &P);
    for (int i = 0; i < P; ++i) {
        scanf("%d", &potion[i]);
    }
    int curr = 0, prev = 1;
    dp[curr][ODD] = potion[0], dp[curr][EVEN] = 0;
    for (int i = 1; i < P; ++i) {
        curr ^= 1, prev ^= 1;
        dp[curr][ODD] = max(dp[prev][ODD], dp[prev][EVEN] + potion[i]);
        dp[curr][EVEN] = max(dp[prev][EVEN], dp[prev][ODD] - potion[i]);
    }
    printf("%d\n", max(dp[curr][ODD], dp[curr][EVEN]));
    return 0;
}

