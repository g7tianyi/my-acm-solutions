/**
 * HDU 2955, Robberies
 * DP.
 */
#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) - (b) > 0.00000001 ? (a): (b))

int money[101];
double prob[101], dp[10001];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        double maxProb;
        int nBank, sum = 0;
        scanf("%lf %d", &maxProb, &nBank);
        maxProb = 1 - maxProb;
        for (int i = 0; i < nBank; ++i) {
            scanf("%d %lf", &money[i], &prob[i]);
            prob[i] = 1 - prob[i];
            sum += money[i];
        }
        /**
         * 0-1 packing problem, but it is a little fresh when it come with probabilities
         * F(i) is the max escaping probability of robbing i money
         * F(i) = MAX(F(i), F(i - money[j]) * prob[j])
         */
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < nBank; ++i) {
            for (int j = sum; j > 0; --j) {
                if (j >= money[i]) {
                    dp[j] = MAX(dp[j], dp[j - money[i]] * prob[i]);
                }
            }
        }
        for (int i = sum; i >= 0; i--) {
            if (dp[i] >= maxProb) {
                printf("%d\n", i);
                break;
            }
        }
    }

    return 0;
}

