/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1024
 *
 * Max Sum Plus Plus, advanced version of max continuous subarray.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_ELEM = 1000002,
    MIN_INF  = -99999999
};

int elems[MAX_ELEM];
int dp[2][MAX_ELEM];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int pair, len;
    while (scanf("%d %d", &pair, &len) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= len; ++i) {
            scanf("%d", &elems[i]);
        }
        // dp[i][j] is the max sum of picking up i sections from [0, j]
        // dp[i][j] = {
        //    dp[i-1][j-1] + elems[j],                   if i == j (#1)
        //    max { dp[i-1][k], dp[i][j-1] } + elems[j], if i != j (#2)
        // }
        // #1 means each single j elements count as one single section
        // #2 means array[j] either being appended to the last section
        //    or counts as a separate section
        int curr = 0, prev = 1, temp;
        for (int i = 1; i <= pair; ++i) {
            temp = MIN_INF;
            for (int j = i; j <= len; ++j) {
                dp[curr][j] = max(dp[curr][j - 1], dp[prev][j - 1]) + elems[j];
                dp[prev][j - 1] = temp;
                temp = max(temp, dp[curr][j]);
            }
        }
        printf("%d\n", temp);
    }
    return 0;
}

