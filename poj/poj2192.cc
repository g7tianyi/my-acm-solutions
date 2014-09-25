/**
 * POJ 2192, Zipper
 *
 * DP.
 *
 * F(i, j), the possibility of using the first i letters of
 * buf1 and the first j letters of buf2 to compose the first
 * L = i + j letters of buff.
 *
 * F(i, j) = {
 *   (F(k, L-k-1) && buff[L] == buf1[k+1]) || (F(L-k-1, k) && buff[L] == buf2[k+1]),
 *   where L = i + j, the prefix length of buff and k in [0, min(len(buf1), L))
 * }
 */
#include <cstdio>
#include <cstring>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int MAX_LEN = 256;
char buf1[MAX_LEN], buf2[MAX_LEN];
char buff[MAX_LEN << 1];
bool dp[MAX_LEN][MAX_LEN];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%s %s %s", buf1, buf2, buff);
        memset(dp, false, sizeof(dp));

        dp[0][0] = true;
        int len1 = strlen(buf1), len2 = strlen(buf2);
        for (int i = 0; i <= len1; ++i) {
            for (int j = 0; j <= len2; ++j) {
                if (i > 0 && dp[i - 1][j] && buf1[i - 1] == buff[i + j - 1]) {
                    dp[i][j] = true;
                }
                if (j > 0 && dp[i][j - 1] && buf2[j - 1] == buff[i + j - 1]) {
                    dp[i][j] = true;
                }
            }
        }

        if (dp[len1][len2]) {
            printf("Data set %d: yes\n", t);
        } else {
            printf("Data set %d: no\n", t);
        }
    }

    return 0;
}

