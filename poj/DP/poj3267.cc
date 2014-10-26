/**
 * http://poj.org/problem?id=3267
 *
 * dynamic programming
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_WORDS = 602,
    MAX_WORD_LEN = 26,
    MAX_TEXT_LEN = 302
};

char dict[MAX_WORDS][MAX_WORD_LEN];
char text[MAX_TEXT_LEN];

int lens[MAX_WORDS];
int dp[MAX_TEXT_LEN];

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int W, L;
    scanf("%d %d", &W, &L);
    scanf("%s", text);
    for (int i = 0; i < W; ++i) {
        scanf("%s", dict[i]);
        lens[i] = strlen(dict[i]);
    }

    dp[0] = 0;
    int i, j, kw, kt, k;
    for (i = 1; i <= L; ++i) { // loop each character of the text
        dp[i] = dp[i - 1] + 1; // means delete i to meet the standard
        for (j = 0; j < W; ++j) { // loop each character of the word
            k = kt = i - 1;   // index of text
            kw = lens[j] - 1; // index of word
            for (; kt >= 0 && kw >= 0; --kt) {
                if (text[kt] == dict[j][kw]) {
                    --kw;
                }
            }
            if (kw < 0) { // finished matching for word j
               // (k - kt) is the length of the backward steps
               dp[i] = min(dp[i], dp[kt + 1] + (k - kt - lens[j]));
            }
        }
    }
    printf("%d\n", dp[L]);

    return 0;
}

