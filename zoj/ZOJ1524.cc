/**
 * ZOJ 1524 Supermarket
 * dynamic programming
 */
#include <iostream>
#include <cstdio>
#include <cmath>
static const double MAX_COST = 1000000000.0;
enum {
    MAX_ITEM = 101,
    MAX_PROD = 100001,
};

int M, N; // M, number of items to buy. N, number of products
int items[MAX_ITEM], prods[MAX_PROD];
double costs[MAX_PROD];
double dp[MAX_ITEM];

int main() {
    while (scanf("%d%d", &M, &N) != EOF && M && N) {
        for (int i = 0; i < M; ++i) {
            scanf("%d", &items[i]);
        }
        for (int i = 0; i < N; ++i) {
            scanf("%d%lf", &prods[i], &costs[i]);
        }

        for (int i = 0; i <= M; ++i) {
            dp[i] = MAX_COST;
        }
        dp[0] = 0;

        // dp(i, j), minimum cost when buying the first j items from the first i products
        // dp(i, j) = min { dp(i-1, j), dp(i-1, j-1) + costs(i) for all prods(i)=items(j) }
        for (int i = 0; i < N; ++i) {
            for (int j = M; j > 0; --j) { // tricky skill, avoid two arrays ^_^
                if (prods[i] == items[j - 1]) {
                    dp[j] = std::min(dp[j], dp[j - 1] + costs[i]);
                }
            }
        }

        if (dp[M] != MAX_COST) {
            printf("%.2lf\n", dp[M]);
        } else {
            printf("Impossible\n");
        }
    }

    return 0;
}

