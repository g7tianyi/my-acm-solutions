/**
 * POJ 3461, Oulipo
 * KMP
 */
#include <cstring>
#include <iostream>

enum {
    MAX_WORD_LEN = 10005,
    MAX_TEXT_LEN = 1000005
};

char word[MAX_WORD_LEN];
char text[MAX_TEXT_LEN];
int  fail[MAX_WORD_LEN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", word, text);
        int wordlen = strlen(word);
        int textlen = strlen(text);

        // KMP: prepare fail pointers
        fail[0] = -1;
        int i = 0, j = -1;
        while (i < wordlen) {
            if (j == -1 || word[i] == word[j]) {
                fail[++i] = ++j;
            } else {
                j = fail[j];
            }
        }

        // KMP: search text
        i = j = 0;
        int result = 0;
        while (i < textlen) {
            if (j == -1 || text[i] == word[j]) {
                ++i; ++j;
                if (j == wordlen) { // found one matching substring
                    j = fail[j];
                    ++result;
                }
            } else {
                j = fail[j];
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

