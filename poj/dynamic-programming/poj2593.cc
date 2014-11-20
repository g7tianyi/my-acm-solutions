/**
 * http://poj.org/problem?id=2593
 *
 * dynamic programming. range sum problem
 */

#include <iostream>

enum {
    ARR_LEN = 100003,
    MIN_INF = -2147483648
};
int arr[ARR_LEN], dp[ARR_LEN];
int len;

int main() {
    while (scanf("%d", &len) != EOF && len) {
        for (int i = 1; i <= len; ++i) {
            scanf("%d", &arr[i]);
        }

        memset(dp, 0, sizeof(dp));
        int maxsum = MIN_INF, cursum = MIN_INF;
        for (int i = 1; i <= len; ++i) {
            if (cursum > 0) {
                cursum += arr[i];
            } else {
                cursum = arr[i];
            }
            if (maxsum < cursum) {
                maxsum = cursum;
            }
            dp[i] = maxsum;
        }

        int result = MIN_INF;
        maxsum = MIN_INF, cursum = MIN_INF;
        for (int i = len; i > 1; --i) {
            if (cursum > 0) {
                cursum += arr[i];
            } else {
                cursum = arr[i];
            }
            if (maxsum < cursum) {
                maxsum = cursum;
            }
            if (result < maxsum + dp[i - 1]) {
                result = maxsum + dp[i - 1];
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

