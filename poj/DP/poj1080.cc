/**
 * POJ 1018
 * dp. Given the not-so-large data volume, BFS might also be an acceptable choice.
 *
 * F(i,j), min cost after choosing from the first i devices and get capacity j
 * F(i,j) =  min { F[i][c], F[i - 1][c] + p }, for all capacity c
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

enum {
    MAX_COST     = 0x7FFFFFFF,
    MAX_VENDOR   = 102,
    MAX_CAPACITY = 1502
};

int dp[MAX_VENDOR][MAX_CAPACITY];

int main() {
    int cases;
    scanf("%d", &cases);

    while (cases--) {

        memset(dp, MAX_COST, sizeof(dp));

        int devices;
        scanf("%d", &devices);

        for (int i = 0; i < MAX_VENDOR; ++i) {
            for (int j = 0; j < MAX_CAPACITY; ++j) {
                dp[i][j] = MAX_COST;
            }
        }

        int vendors, capacity, price;
        for (int i = 1; i <= devices; i++) {
            scanf("%d", &vendors);
            for (int j = 1; j <= vendors; j++) {
                scanf("%d %d", &capacity, &price);
                if (i == 1) {
                    dp[i][capacity] = min(dp[i][capacity], price);
                } else {
                    for (int c = 0; c < MAX_CAPACITY; ++c) {
                        if (dp[i - 1][c] != MAX_COST) {
                            if (c <= capacity) {
                                dp[i][c] = min(dp[i][c], dp[i - 1][c] + price);
                            } else {
                                dp[i][capacity] = min(dp[i][capacity], dp[i - 1][c] + price);
                            }
                        }
                    }
                }
            }
        }

        double res = 0, tmp;
        for (int i = 0; i < MAX_CAPACITY; i++) {
            if (dp[devices][i] != MAX_COST) {
                tmp = ((double) i) / dp[devices][i];
                if (res < tmp) {
                    res = tmp;
                }
            }
        }
        printf("%.3lf\n", res);
    }

    return 0;
}

