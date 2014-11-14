/**
 * http://poj.org/problem?id=2013
 */

#include <iostream>
#include <cstring>

char words[16][32];

int main() {
    int T = 1, size;
    while (scanf("%d", &size) != EOF && size) {
        for (int i = 0; i < size; ++i) {
            scanf("%s", words[i]);
        }

        printf("SET %d\n", T++);
        for (int i = 0; i < size; i += 2) {
            printf("%s\n", words[i]);
        }
        for (int i = size - 1 - (size & 0x1u); i > 0; i -= 2) {
            printf("%s\n", words[i]);
        }
    }
    return 0;
}

