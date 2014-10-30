/**
 * http://poj.org/problem?id=2479
 *
 * Maximum sum
 *
 * dynamic programming, range sum problem
 */

#include <limits>
#include <cstdio>
#include <cstring>

enum {
    MAX_LEN = 50010, MIN_INF = -2147483648
};

int arr[MAX_LEN], dp[MAX_LEN];

int main() {
    int cases, len;

    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &len);
        for (int i = 1; i <= len; i++) {
            scanf("%d", &arr[i]);
        }

        memset(dp, 0, sizeof(dp));
        int maxsum = MIN_INF, cursum = MIN_INF;
        for (int i = 1; i <= len; i++) {
            if (cursum > 0) {
                cursum += arr[i];
            } else {
                cursum = arr[i];
            }
            if (cursum > maxsum) {
                maxsum = dp[i] = cursum;
            }
        }

        int result = MIN_INF;
        cursum = 0, maxsum = MIN_INF;
        for (int i = len; i > 1; i--) {
            if (cursum > 0) {
                cursum += arr[i];
            } else {
                cursum = arr[i];
            }
            if (cursum > maxsum) {
                maxsum = cursum;
            }
            if (maxsum + dp[i - 1] > result) {
                result = maxsum + dp[i - 1];
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

