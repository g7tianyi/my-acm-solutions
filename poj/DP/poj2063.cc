/**
 * POJ 2063, Investment
 * DP. Try binary optimization
 */
#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

enum {
    FACTOR = 1000, MAX_BOUD = 16, MAX_OPTION = 400000
};
struct BOND {
    int price, value;
};
BOND bond[MAX_BOUD];
int dp[MAX_OPTION];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int amount; // could go to 1,000,000 * 2^40
        int years, num_bond;
        scanf("%d %d", &amount, &years);
        scanf("%d", &num_bond);
        for (int i = 0; i < num_bond; ++i) {
            scanf("%d %d", &bond[i].price, &bond[i].value);
            bond[i].price /= FACTOR;
        }

        while (years--) {
            memset(dp, 0, sizeof(dp));
            for (int i = 0; i < num_bond; ++i) {
                for (int j = bond[i].price; j <= amount / FACTOR; ++j) {
                    dp[j] = MAX(dp[j], dp[j - bond[i].price] + bond[i].value);
                }
            }
            amount += dp[amount / FACTOR];
        }

        printf("%d\n", amount);
    }

    return 0;
}

