/**
 * http://poj.org/problem?id=1723
 *
 * SOLDIERS
 *
 * sort. median
 */

#include <cstdio>
#include <algorithm>

const int MAX_SOLDIER = 10002;

int xpos[MAX_SOLDIER];
int ypos[MAX_SOLDIER];
int xtmp[MAX_SOLDIER];

inline int myabs(int a) {
    return a > 0 ? a : -a;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &xpos[i], &ypos[i]);
        }
        std::sort(xpos, xpos + N);
        std::sort(ypos, ypos + N);
        // The soldiers want to get into a horizontal line next to each other
        // (so that their final positions are (x,y), (x+1,y), ..., (x+N-1,y),
        // for some x and y)
        // ... >_< totally no idea what it is in the first sight...
        for (int i = 0; i < N; ++i) {
            xtmp[i] = xpos[i] - i - 1;
        }
        std::sort(xtmp, xtmp + N);

        int result = 0, med = N >> 1;
        for (int i = 0; i < N; ++i) {
            result += (myabs(xtmp[i] - xtmp[med]) + myabs(ypos[i] - ypos[med]));
        }
        printf("%d\n", result);
    }
    return 0;
}

