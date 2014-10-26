/**
 * http://poj.org/problem?id=1836
 *
 * dynamic programming, refer to poj 2533
 */

#include <cstdio>

const int MAX_SOLIDER = 1001;
float height[MAX_SOLIDER];
int increase[MAX_SOLIDER];
int decrease[MAX_SOLIDER];

int main() {
    int soldiers;
    scanf("%d", &soldiers);

    for (int i = 0; i < soldiers; ++i) {
        scanf("%f", &height[i]);
        increase[i] = decrease[i] = 1;
    }

    for (int i = 0; i < soldiers; ++i) {
        for (int j = 0; j < i; ++j) {
            if (height[j] < height[i] && increase[i] < increase[j] + 1) {
                increase[i] = increase[j] + 1;
            }
        }
    }

    for (int i = soldiers - 1; i >= 0; --i) {
        for (int j = i + 1; j < soldiers; ++j) {
            if (height[j] < height[i] && decrease[i] < decrease[j] + 1) {
                decrease[i] = decrease[j] + 1;
            }
        }
    }

    // try split from i, [0...i] asc,  (i...N) desc
    int maxlen = 0;
    for (int i = 0; i < soldiers - 1; ++i) {
        for (int j = i + 1; j < soldiers; ++j) {
            if (maxlen < increase[i] + decrease[j]) {
                maxlen = increase[i] + decrease[j];
            }
        }
    }
    printf("%d\n", soldiers - maxlen);

    return 0;
}

