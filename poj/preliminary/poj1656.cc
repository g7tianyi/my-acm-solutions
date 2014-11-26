/**
 * http://poj.org/problem?id=1656
 * Counting Black
 */

#include <iostream>

bool map[101][101];
char buf[8];

int main() {
    int C, X, Y, L;
    scanf("%d", &C);
    memset(map, false, sizeof(map));
    while (C--) {
        scanf("%s %d %d %d", buf, &X, &Y, &L);
        if (strcmp(buf, "TEST") == 0) {
            int result = 0;
            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L; ++j) {
                    result += map[X + i][Y + j];
                }
            }
            printf("%d\n", result);
        } else {
            bool seed = (strcmp(buf, "BLACK") == 0);
            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L; ++j) {
                    map[X + i][Y + j] = seed;
                }
            }
        }
    }
    return 0;
}

