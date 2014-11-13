/**
 * POJ 3254, Corn Fields
 * DP. State compression.
 *
 * F(i, j) is the max solutions for row i in state j
 * F(i, j) = sum { F(i-1, k) if state j not conflict with row state and state k }
 * F(0, j) = 1 if state j not conflict with row state
 *
 * more about state.
 * for each row, if a grid in this row is fertile, mark the related bit with 0, else 1.
 * for each arrangement, say
 * | Y | Y | N | N |
 * The state is 1100 => 6. ('Y' indicate a cow in that grid)
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_M = 16,
    MAX_N = 16,
    MOD = 100000000
};

int fields[MAX_M];
int states[1 << MAX_N];
int dp[2][1 << MAX_N];

int M, N, num_state;

int main() {
    scanf("%d %d", &M, &N);

    int i, j;
    int field, grid;
    for (i = 0; i < M; ++i) {
        field = 0;
        for (j = 0; j < N; ++j) {
            scanf("%d", &grid);
            field <<= 1;
            field |= (grid == 0 ? 1 : 0);
        }
        fields[i] = field;
    }

    j = 0;
    for (i = 0; i < (1 << N); ++i) {
        if (!(i & (i << 1))) { // can not put cows in two adjacent grids
            states[j++] = i;
        }
    }
    num_state = j;

    memset(dp, 0, sizeof(dp));
    int curr = 0, prev = 1;
    for (i = 0; i < num_state; ++i) {
        dp[curr][i] = (states[i] & fields[0]) ? 0 : 1;
    }

    int k;
    for (i = 1; i < M; ++i) { // try each row
        curr ^= 1, prev ^= 1;
        memset(dp[curr], 0, sizeof(dp[0]));
        for (j = 0; j < num_state; ++j) { // try each state in this row
            if (states[j] & fields[i]) {
                continue;
            }
            for (k = 0; k < num_state; ++k) { // try each state in the previous row
                if ((states[k] & fields[i - 1]) || (states[k] & states[j])) {
                    continue;
                }
                dp[curr][j] = (dp[curr][j] + dp[prev][k]) % MOD;
            }
        }
    }

    int result = 0;
    for (i = 0; i < num_state; ++i) {
        result = (result + dp[curr][i]) % MOD;
    }
    printf("%d\n", result);

    return 0;
}

