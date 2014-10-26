/**
 * POJ 3311, Hie with the Pie
 * DP. State compression.
 *
 * F(i, curr) is the min cost when postman ending in city i with state curr
 * F(i, curr) = min { F(k, prev) for all city k with state prev (curr = prev | k) }
 */
#include <cstdio>
#include <cstring>
typedef unsigned int uint;

enum {
    MAX_N = 12, MAX_TIME = 400000000
};

const uint STATES[MAX_N] = { 0, 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1
        << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10 };
uint times[MAX_N][MAX_N];
uint dp[1 << MAX_N][MAX_N];

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N) {
        uint i, j, k;
        for (i = 0; i <= N; ++i) {
            for (j = 0; j <= N; ++j) {
                scanf("%d", &times[i][j]);
            }
        }

        // flyod algo
        for (i = 0; i <= N; ++i) {
            for (j = 0; j <= N; ++j) {
                for (k = 0; k <= N; ++k) {
                    if (times[j][k] > times[j][i] + times[i][k]) {
                        times[j][k] = times[j][i] + times[i][k];
                    }
                }
            }
        }

        uint max_state = (1 << N) - 1;
        for (i = 1; i <= max_state; ++i) {
            for (j = 1; j <= N; ++j) {
                dp[i][j] = MAX_TIME;
            }
        }

        uint prev;
        for (i = 1; i <= max_state; ++i) {
            for (j = 1; j <= N; ++j) {
                if (i & STATES[j]) {
                    if (i == STATES[j]) {
                        dp[i][j] = times[0][j];
                    } else {
                        prev = i ^ STATES[j]; // prev state
                        for (k = 1; k <= N; ++k) {
                            if (!(i & STATES[k]) || k == j) {
                                continue;
                            }
                            if (dp[i][j] > dp[prev][k] + times[k][j]) {
                                dp[i][j] = dp[prev][k] + times[k][j];
                            }
                        }
                    }
                }
            }
        }

        // need to go back to Pizzeria
        int result = dp[max_state][1] + times[1][0];
        for (i = 2; i <= N; ++i) {
            if (result > dp[max_state][i] + times[i][0]) {
                result = dp[max_state][i] + times[i][0];
            }
        }
        printf("%d\n", result);
    }

    return 0;
}

