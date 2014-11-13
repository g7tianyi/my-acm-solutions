/**
 * http://poj.org/problem?id=2955
 *
 * Brackets
 *
 * DP. String. Brackets.
 *
 * Compare it with poj 1141
 */

#include <cstdio>
#include <cstring>

const int MAX_LEN = 105;

char buf[MAX_LEN];
int dp[MAX_LEN][MAX_LEN];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    while (scanf("%s", buf) != EOF) {
        if (strcmp(buf, "end") == 0) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        int len = strlen(buf);
        for (int l = 0; l < len; ++l) {
            for (int i = 0, j = l; j < len; ++i, ++j) {
                if ((buf[i] == '(' && buf[j] == ')')
                        || (buf[i] == '[' && buf[j] == ']')) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
                }
                for (int k = i; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        printf("%d\n", dp[0][len - 1]);
    }
    return 0;
}

