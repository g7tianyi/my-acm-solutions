/**
 * http://poj.org/problem?id=2334
 *
 * string prefix. simple.
 */

#include <iostream>

char buf[10001][256];

// length of common prefix
inline int prelen(char* s1, char* s2) {
    int len = 0;
    while(*s1 && *s2 && *s1++ == *s2++) {
        ++len;
    }
    return len;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", buf[i]);
    }

    int result = strlen(buf[0]), plen;
    for (int i = 1; i < N; ++i) {
        plen = prelen(buf[i], buf[i-1]);
        result += (strlen(buf[i]) - plen + 1);
    }
    printf("%d\n", result);

    return 0;
}

