/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1024
 *
 * Max Sum Plus Plus, advanced version of max continuous subarray.
 */

#include <cstdio>
#include <cstring>

const int MAX_ELEM = 1000001;

int array[MAX_ELEM];
int dp[2][MAX_ELEM];

int main() {
    int pair, len;
    while (scanf("%d %d", &pair, &len) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < len; ++i) {
            scanf("%d", &array[i]);
        }
        // dp[i][j] is the max sum of picking up i sections from [0, j]
        // dp[i][j] = {
        //    dp[i-1][j-1] + array[j],                   if i == j (#1)
        //    max { dp[i-1][k], dp[i][j-1] } + array[j], if i != j (#2)
        // }
        // #1 means each single j elements count as one single section
        // #2 means array[j] either being appended to the last section
        //    or counts as a separate section
        //
        // this implementation takes the advantage of the sliding array
        int curr = 0, prev = 1;
        for (int i = 0; i < pair; ++i) {
            curr ^= 1, prev ^= 1;
            dp[curr][i] = (i > 0 ? dp[prev][i - 1] : 0) + array[i];
            for (int j = i + 1; j < len; ++j) {
                dp[curr][j] = dp[curr][j - 1];
                for (int k = i - 1; k < j; ++k) {
                    if (dp[curr][j] < dp[prev][k]) {
                        dp[curr][j] = dp[prev][k];
                    }
                }
                dp[curr][j] += array[j];
            }
        }

        int result = dp[curr][pair - 1];
        for (int i = pair; i < len; ++i) {
            if (result < dp[curr][i]) {
                result = dp[curr][i];
            }
        }
        printf("%d\n", result);
    }
    return 0;
}

