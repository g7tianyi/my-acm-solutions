/**
 * http://poj.org/problem?id=2533
 *
 * dynamic programming
 */

#include <cstdio>

const int MAX_SEQ = 1002;
int seq[MAX_SEQ];
int dp[MAX_SEQ];

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &seq[i]);
        dp[i] = 1;
    }

    // dp(i), longest ordered length ending precisely in i
    // dp(i) = max { dp(j) + 1 | j in [0, i -1], seq[j] < seq[i] } 
    int result = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (seq[j] < seq[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
        if (result < dp[i]) {
            result = dp[i];
        }
    }
    printf("%d\n", result);

    return 0;
}

