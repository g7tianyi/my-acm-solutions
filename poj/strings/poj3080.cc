/**
 * http://poj.org/problem?id=3080
 *
 * KMP
 */

#include <iostream>

enum {
    MAX_SEQ = 12,
    MAX_LEN = 64,
    BASE    = 60
};

struct KMP {
public:
    void init(char* word, int len) {
        memset(__next, 0, sizeof(__next));
        memset(__word, 0, sizeof(__word));
        strcpy(__word, word);
        __next[0] = -1;
        int i = 0, j = -1;
        while (i < len - 1) {
            if (j == -1 || word[i] == word[j]) {
                __next[++i] = ++j;
            } else {
                j = __next[j];
            }
        }
    }

    int search(char* text, int textlen) {
        int wordlen = strlen(__word);
        int i = 0, j = 0;
        while (i < textlen && j < wordlen) {
            if (j == -1 || text[i] == __word[j]) {
                ++i, ++j;
            } else {
                j = __next[j];
            }
        }
        if (j == wordlen) {
            return i - j;
        } else {
            return -1;
        }
    }

private:
    char __word[MAX_LEN];
    int  __next[MAX_LEN];
};

KMP  kmp;
char text[MAX_SEQ][MAX_LEN];
char buff[MAX_LEN];
char word[MAX_LEN];

int main() {
    int T, M;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &M);
        for (int i = 0; i < M; ++i) {
            scanf("%s", text[i]);
        }

        memset(buff, 0, sizeof(buff));
        int res = 0, len = 3;
        for (; len <= BASE; ++len) {
            bool found = false;
            for (int i = 0; i + len <= BASE; ++i) { // i is the start pos of the substr
                memset(word, 0, sizeof(word));
                memcpy(word, text[0] + i, len);
                kmp.init(word, len);

                bool valid = true;
                for (int j = 1; j < M; ++j) { // try each sequence
                    if (kmp.search(text[j], BASE) == -1) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    found = true;
                    if (res < len || (res == len && strcmp(word, buff) < 0)) {
                        res = len;
                        strcpy(buff, word);
                    }
                }
            }

            if (!found) {
                break;
            }
        }

        if (res) {
            printf("%s\n", buff);
        } else {
            printf("no significant commonalities\n");
        }
    }
    return 0;
}

