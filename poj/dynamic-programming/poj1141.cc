/**
 * http://poj.org/problem?id=1141
 * Brackets Sequence
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_LEN = 220, MAX_INF = 0x7fffffff
};

char buf[MAX_LEN];
int dp[MAX_LEN][MAX_LEN];
int pos[MAX_LEN][MAX_LEN];

void output(int i, int j) {
    if (i > j) {
        return;
    }
    if (i == j) {
        if (buf[i] == '(' || buf[i] == ')') {
            printf("()");
        } else {
            printf("[]");
        }
    } else if (pos[i][j] == -1) {
        printf("%c", buf[i]);
        output(i + 1, j - 1);
        printf("%c", buf[j]);
    } else {
        output(i, pos[i][j]);
        output(pos[i][j] + 1, j);
    }
}

int main() {
    scanf("%s", buf);
    int len = strlen(buf);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < len; i++) {
        dp[i][i] = 1;
    }

    // dp[i][j] means how many brackets should be added to make range[i, j] valid
    for (int k = 1; k < len; ++k) { // length
        for (int i = 0; i + k < len; ++i) { // begin
            int j = i + k;
            dp[i][j] = MAX_INF;
            if ((buf[i] == '(' && buf[j] == ')')
                    || (buf[i] == '[' && buf[j] == ']')) { // (#)
                // matched
                // ...(([][])...
                //    |     |
                //    i     j
                dp[i][j] = dp[i + 1][j - 1];
                pos[i][j] = -1;
            }
            // why the following loop must run ?
            //   ...()([][])...
            //      |      |
            //      i      j
            // dp[i+1][j-1] = 2 (#) give us dp[i][j] = 2
            // but as we can see, dp[i][j] = 0 is the best option
            for (int s = i; s < j; ++s) { // split
                if (dp[i][j] > dp[i][s] + dp[s + 1][j]) {
                    dp[i][j] = dp[i][s] + dp[s + 1][j];
                    pos[i][j] = s;
                }
            }
        }
    }

    output(0, len - 1);
    printf("\n");
    return 0;
}

