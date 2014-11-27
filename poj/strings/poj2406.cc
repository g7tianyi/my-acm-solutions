/**
 * POJ 2406, Power Strings
 * KMP, KMP's fail array is really amazing
 */
#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 1000005;
char text[MAX_LENGTH];
int  fail[MAX_LENGTH];

int main() {
    while (scanf("%s", text) != EOF && text[0] != '.') {
        int textlen = strlen(text);
        // KMP: prepare fail pointers
        fail[0] = -1;
        int i = 0, j = -1;
        while (i < textlen) {
            if (j == -1 || text[i] == text[j]) {
                fail[++i] = ++j;
            } else {
                j = fail[j]; // backtrack j
            }
        }
        int last = fail[textlen];
        if (textlen % (textlen - last) == 0) {
            printf("%d\n", textlen / (textlen - last));
        } else {
            // case: ababxababxab, should avoid such WA >_<
            printf("1\n");
        }
    }
    return 0;
}
