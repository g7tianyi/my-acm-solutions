/**
 * POJ 1458 Common Subsequence
 * DP LCS
 */
#include <cstdio>
#include <cstring>

#define max(a, b) ((a) > (b) ? (a) : (b))

char buf1[1024];
char buf2[1024];
int dp[1025][1025];

int main() {

    while (scanf("%s %s", buf1, buf2) != EOF) {

        // dp(i,j), longest common subsequence of the first i
        // characters of buf1 and the first j characters of buf2
        // dp(i,j) = {
        //    if buf1[i] == buf2[j], dp(i-1, j-1) + 1
        //    else max(dp(i, j-1), dp(i-1, j))
        // }
        memset(dp, 0, sizeof(dp));
        int len1 = strlen(buf1), len2 = strlen(buf2);
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (buf1[i - 1] == buf2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        printf("%d\n", dp[len1][len2]);
    }

    return 0;
}

