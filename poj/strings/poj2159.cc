/**
 * http://poj.org/problem?id=2159
 * string. hash.
 */
#include <algorithm>
#include <iostream>

enum TextType {
    CIPHER, // 0
    PLAIN , // 1
    TYPE_COUNT
};

enum {
    ALPHABET   = 26,
    MAX_LETTER = 256
};

const int PRIME[ALPHABET] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67,
    71, 73, 79, 83, 89, 97, 101
};

char buf[TYPE_COUNT][MAX_LETTER];
int count[TYPE_COUNT][ALPHABET];

int main() {
    scanf("%s %s", buf[CIPHER], buf[PLAIN]);

    memset(count, 0, sizeof(count));
    int len = strlen(buf[CIPHER]);
    bool result = true;
    if (len == strlen(buf[PLAIN])) {
        for (int i = 0; i < len; ++i) {
            ++count[CIPHER][buf[CIPHER][i] - 'A'];
            ++count[PLAIN][buf[PLAIN][i] - 'A'];
        }

        std::sort(count[CIPHER], count[CIPHER] + ALPHABET);
        std::sort(count[PLAIN], count[PLAIN] + ALPHABET);
        int cipher = 0, plain = 0;
        for (int i = 0; i < ALPHABET; ++i) {
            cipher += count[CIPHER][i] * PRIME[i];
            plain += count[PLAIN][i] * PRIME[i];
        }
        result = (cipher == plain);
    } else {
        result = false;
    }

    if (result) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}

