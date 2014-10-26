/**
 * http://poj.org/problem?id=1260
 *
 * dynamic programming
 */

#include <cstdio>

const int MAX_PEARL = 102;

int amount[MAX_PEARL];
int prices[MAX_PEARL];

int count[MAX_PEARL];
int dp[MAX_PEARL];

int main() {
    int cases;
    scanf("%d", &cases);

    int pearl;
    while (cases--) {
        scanf("%d", &pearl);
        count[0] = 0, dp[0] = 0;
        for (int i = 1; i <= pearl; ++i) {
            scanf("%d %d", &amount[i], &prices[i]);
            count[i] = count[i - 1] + amount[i];
        }

        // the qualities of the classes (and so the prices) are given in ascending order.
        // thus no need to sort, good.

        for (int i = 1, temp; i <= pearl; ++i) {
            dp[i] = dp[i - 1] + (amount[i] + 10) * prices[i];
            for (int j = 0; j < i; ++j) {
                // buy pearls of categories in [j + 1, i] with price of category i
                temp = (count[i] - count[j] + 10) * prices[i] + dp[j];
                if (dp[i] > temp) {
                    dp[i] = temp;
                }
            }
        }

        printf("%d\n", dp[pearl]);
    }

    return 0;
}

