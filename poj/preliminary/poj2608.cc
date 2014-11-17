/**
 * http://poj.org/problem?id=2608
 */

#include <iostream>

int map[26] = { -1, 1, 2, 3, -1, 1, 2, -1, -1, 2, 2, 4, 5, 5, -1, 1, 2, 6, 2, 3, -1, 1,
        -1, 2, -1, 2 };

char buf[32];

/**
 * stupid mapping...
 *
 * 1  B F P V
 * 2  C G J K Q S X Z
 * 3  D  T
 * 4  L
 * 5  M  N
 * 6  R
 * 0
 *  memset(map, -1, sizeof(map));
    int num;
    char ch;
    while (scanf("%d", &num) != EOF && num) {
        while ((ch = getchar()) != '\n') {
            if (ch < 'A' || ch > 'Z') {
                continue;
            }
            map[ch - 'A'] = num;
        }
    }
    printf("int map[26] = {\n");
    for (int i = 0; i < 26; ++i) {
        printf("%d,", map[i]);
    }
    printf("\n};");
 */
int main() {
    while(scanf("%s", buf) != EOF) {
        int len = strlen(buf);
        for (int i = 0, prev = 0; i < len; ++i) {
            if (map[buf[i] - 'A'] > 0 && prev != map[buf[i] - 'A']) {
                putchar(map[buf[i] - 'A'] + '0');
            }
            prev = map[buf[i] - 'A'];
        }
        putchar('\n');
    }
    return 0;
}

