/**
 * POJ 1837, Balance
 * DP
 */
#include <cstdio>
#include <cstring>

// MAX_HASH_SHIFT = ((2 << 11) + (2 << 10) + (2 << 9) + (2 << 8) + (2 << 7)) << 1
// maximum/minimum is 25 * 20 * 15 = 7500
enum {
    MAX_WEIGHTS = 24,
    MAX_POSITIONS = 24,
    MAX_HASH_VALUE = 16000,
    MAX_HASH_SHIFT = 10000
};

int pos[MAX_POSITIONS];
int values[MAX_WEIGHTS][MAX_POSITIONS];
int dp[MAX_WEIGHTS][MAX_HASH_VALUE];

inline int abs(int a) {
    return a > 0 ? a : -a;
}
inline int abs_max(int a, int b) {
    a = abs(a), b = abs(b);
    return a > b ? a : b;
}
inline int hash(int num) {
    return num >= 0 ? num : (num + MAX_HASH_SHIFT);
}

int main() {

    int num_pos, num_weight;
    scanf("%d %d", &num_pos, &num_weight);
    int i;
    for (i = 0; i < num_pos; ++i) {
        scanf("%d", &pos[i]);
    }
    int j, weight;
    for (i = 0; i < num_weight; ++i) {
        scanf("%d", &weight);
        for (j = 0; j < num_pos; ++j) {
            values[i][j] = weight * pos[j];
        }
    }

    // F(i, v), solution count of getting value v by arranging the first i weights
    // F(i, v) = sum { dp[i - 1][v - v']
    //      | v' is all possible values of placing weight i in different positions }
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < num_pos; ++i) {
        dp[0][hash(values[0][i])] = 1;
    }

    int max_val = (MAX_HASH_VALUE >> 1), v;
    for (i = 1; i < num_weight; ++i) {
        for (v = -max_val; v <= max_val; ++v) {
            for (j = 0; j < num_pos; ++j) {
                dp[i][hash(v)] += dp[i - 1][hash(v - values[i][j])];
            }
        }
    }
    printf("%d\n", dp[num_weight - 1][hash(0)]);

    return 0;
}

