/**
 * HDU 1203, I NEED A OFFER!
 * http://acm.hdu.edu.cn/showproblem.php?pid=1203
 * DP. 0-1 packing
 */
#include <cstdio>

const int MAX_MONEY = 10005;
double dp[MAX_MONEY];

inline double min(const double a, const double b) {
    return a < b ? a : b;
}

int main() {
    int money, college;
    while (scanf("%d %d", &money, &college) != EOF && (money || college)) {
        // dp[j], minimum probability of spending j dollars
        // WITHOUT receiving offer
        for (int i = 0; i <= money; ++i) {
            dp[i] = 1;
        }
        int cost;
        double prob;
        for (int i = 0; i < college; ++i) {
            scanf("%d %lf", &cost, &prob);
            for (int j = money; j >= cost; --j) {
                dp[j] = min(dp[j], dp[j - cost] * (1 - prob));
            }
        }
        printf("%.1lf%%\n", (1.0 - dp[money]) * 100.0);
    }
    return 0;
}

