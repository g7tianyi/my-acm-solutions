/**
 * http://poj.org/problem?id=2334
 *
 * WA. function numlen is not necessary, misunderstands the problem description..
 * "where [j] is a single character with code j."
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

// length of a number
//   0 => 1
//   1 => 1
// 123 => 3
inline int numlen(int num) {
    int len = num ? 0 : 1;
    while (num) {
        ++len;
        num /= 10;
    }
    return len;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", buf[i]);
    }

    int result = strlen(buf[0]), plen, nlen;
    for (int i = 1; i < N; ++i) {
        plen = prelen(buf[i], buf[i-1]);
        nlen = numlen(plen);
        result += (strlen(buf[i]) - plen + nlen);
    }
    printf("%d\n", result);

    return 0;
}

