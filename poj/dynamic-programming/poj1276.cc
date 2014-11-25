/**
 * POJ 1276 Cash Machine
 * DP. Change to 0-1 pack problem. Compare with TLE version.
 */
#include <cstdio>
#include <cstring>

enum {
    // 0 <= N <= 10 is the number of bill denominations and 0 <= nk <= 1000
    // MAX_DENO = 10 * log(1000) => 101
    MAX_DENO = 101,
    MAX_CASH = 100005
};

int CASH, DENO;
int value[MAX_DENO];

bool dp[MAX_CASH];

int main() {

    while (scanf("%d %d", &CASH, &DENO) != EOF) {

        memset(value, 0, sizeof(value));

        int num, val, count = 0;
        for (int i = 0; i < DENO; ++i) {
            scanf("%d %d", &num, &val);
            int k = 1;
            while (num >= k) {
                value[count++] = val * k;
                num -= k;
                k <<= 1;
            }
            if (num) {
                value[count++] = val * num;
            }
        }

        memset(dp, false, (CASH + 1) * sizeof(bool));
        dp[0] = true;
        for (int i = 0; i < count; ++i) { // zero-one-pack problem
            for (int k = CASH; k >= value[i]; --k) {
                if (dp[k - value[i]] && !dp[k]) {
                    dp[k] = true;
                }
            }
        }

        int result = CASH;
        while (!dp[result]) {
            --result;
        }

        printf("%d\n", result);

    }

    return 0;
}
