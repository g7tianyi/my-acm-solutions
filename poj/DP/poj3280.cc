/**
 * http://poj.org/problem?id=3280
 *
 * Cheapest Palindrome
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_LEN = 2002,
    MAX_CHAR = 26
};

char buf[MAX_LEN];
int cost[MAX_CHAR];
int dp[MAX_LEN][MAX_LEN];

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int len, num;
    while (scanf("%d %d", &num, &len) != EOF) {
        scanf("%s", buf);
        char alphabets[2];
        int ins, del; // cost of insert, delete
        for (int i = 0; i < num; ++i) {
            scanf("%s %d %d", alphabets, &ins, &del);
            cost[alphabets[0] - 'a'] = min(ins, del);
        }

        // dp[i][j], minimum cost of range[i...j]
        // dp[i][j] = min {
        //     min(dp[i+1][j] + delete buf[i], dp[i+1][j] + insert buf[i]),
        //     min(dp[i][j-1] + delete buf[j], dp[i][j-1] + insert buf[j])
        // }
        memset(dp, 0, sizeof(dp));
        for (int j = 1; j < len; ++j) {
            for (int i = j - 1; i >= 0; --i) {
                // watch out for cases like this
                // ...ababcddcba...
                //    |        |
                //    i        j
                dp[i][j] = min(dp[i + 1][j] + cost[buf[i] - 'a'], // delete/insert a buf[i]
                        dp[i][j - 1] + cost[buf[j] - 'a']); // delete/insert a buf[j]
                if (buf[i] == buf[j]) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
                }
            }
        }
        printf("%d\n", dp[0][len - 1]);
    }
    return 0;
}

