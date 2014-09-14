/**
 * POJ 1742, Coins
 * Multiple-DP problem
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

enum {
    MAX_COINS = 101, MAX_CHOICE = 1200, MAX_MONEY = 100001
};

struct COINS {
    int value, count;
};

inline bool comp(COINS& coin1, COINS& coin2) {
    return coin1.value < coin2.value;
}

COINS coins[MAX_COINS];
int choices[MAX_CHOICE];
bool DP[2][MAX_MONEY];
int ROW;

int main() {
    int N, M; // n, number of different coins. m, money
    while (scanf("%d %d", &N, &M) != EOF && N && M) {
        int i;
        for (i = 0; i < N; ++i) {
            scanf("%d", &(coins[i].value));
        }
        for (i = 0; i < N; ++i) {
            scanf("%d", &(coins[i].count));
        }
        std::sort(coins, coins + N, comp);

        memset(choices, 0, sizeof(choices));
        int num = 1, k, count, value;
        for (i = 0; i < N; ++i) {
            count = coins[i].count;
            value = coins[i].value;
            k = 1;
            while (count >= k) {
                choices[num++] = value * k;
                count -= k;
                k <<= 1;
            }
            if (count) {
                choices[num++] = value * count;
            }
        }

        ROW = 0;
        // DP[i][j] reachability of choosing from the first i coins to get j
        // DP[i][j] = DP[i - 1][j] || DP[i - 1][j - C[i]]
        memset(DP, false, sizeof(DP));
        DP[ROW][choices[1]] = true;
        for (i = 2; i < num; ++i) {
            DP[ROW][0] = true;
            ROW = 1 - ROW;
            for (k = 1; k <= M; ++k) {
                DP[ROW][k] = DP[1 - ROW][k] ||
                        (k >= choices[i] && DP[1 - ROW][k - choices[i]]);
            }
        }

        int result = 0;
        for (k = 1; k <= M; ++k) {
            if (DP[ROW][k]) {
                ++result;
            }
        }
        printf("%d\n", result);
    }

    return 0;
}

