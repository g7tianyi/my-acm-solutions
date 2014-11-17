/**
 * http://poj.org/problem?id=1674
 */

#include <iostream>

static const int MAX_CHAR = 102;
char text[MAX_CHAR][MAX_CHAR];
char buff[MAX_CHAR];

inline void reverse(char* buf, int len) {
    int i = 0, j = len - 1;
    char ch;
    while (i < j) {
        ch = *(buf + i);
        *(buf + i) = *(buf + j);
        *(buf + j) = ch;
        ++i, --j;
    }
}

struct KMP {
public:
    void init(char* word, int len) {
        memset(__next, 0, sizeof(__next));
        memset(__word, 0, sizeof(__word));
        strcpy(__word, word);
        __worlen = len;
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
        int i = 0, j = 0;
        while (i < textlen && j < __worlen) {
            if (j == -1 || text[i] == __word[j]) {
                ++i, ++j;
            } else {
                j = __next[j];
            }
        }
        if (j == __worlen) {
            return i - j;
        } else {
            return -1;
        }
    }
private:
    int  __worlen;
    char __word[MAX_CHAR];
    int  __next[MAX_CHAR];
};

KMP ordinalKmp, reverseKmp;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int num;
        scanf("%d", &num);
        int minlen = MAX_CHAR + 1, minidx = 0;
        for (int i = 0, len; i < num; ++i) {
            scanf("%s", text[i]);
            len = strlen(text[i]);
            if (minlen > len) {
                minlen = len;
                minidx = i;
            }
        }

        int result = 0;
        for (int i = minlen; i > 0; --i) { // length of substr
            for (int j = 0; j + i <= minlen; ++j) { // start pos of substr
                memset(buff, 0, sizeof(buff));
                memcpy(buff, text[minidx] + j, i);
                ordinalKmp.init(buff, i);
                reverse(buff, i);
                reverseKmp.init(buff, i);

                bool valid = true;
                for (int k = 0, len; k < num; ++k) {
                    if (k == minidx) {
                        continue;
                    }
                    len = strlen(text[k]);
                    if (ordinalKmp.search(text[k], len) == -1
                           && reverseKmp.search(text[k], len) == -1) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    result = i;
                    break;
                }
            }

            if (result > 0) {
                break;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

