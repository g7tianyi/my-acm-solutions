/**
 * http://poj.org/problem?id=2350
 */

#include <iostream>

int score[1002];

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int total, sum = 0;
        scanf("%d", &total);
        for (int i = 0; i < total; ++i) {
            scanf("%d", &score[i]);
            sum += score[i];
        }
        int above = 0;
        for (int i = 0; i < total; ++i) {
            if (score[i] * total > sum) {
                ++above;
            }
        }
        printf("%.3f%%\n", (double) (above * 100) / total);
    }
    return 0;
}


