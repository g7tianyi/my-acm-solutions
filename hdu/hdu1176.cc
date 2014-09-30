/**
 * HDU 1176, 免费馅饼
 * http://acm.hdu.edu.cn/showproblem.php?pid=1176
 *
 * Down-Top DP.
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_POS = 11, MAX_TIME = 100002
};

inline int max(int a, int b) {
    return a > b ? a : b;
}

int pie[MAX_TIME][MAX_POS];

int main() {
    int N, pos, time, maxTime, i, j;
    while (scanf("%d", &N) != EOF && N) {
        memset(pie, 0, sizeof(pie));
        maxTime = 0;
        while (N--) {
            scanf("%d %d", &pos, &time);
            pie[time][pos]++;
            if (time > maxTime) {
                maxTime = time;
            }
        }
        for (i = maxTime; i >= 0; i--) {
            pie[i][0] += max(pie[i + 1][0], pie[i + 1][1]);
            for (j = 1; j < 10; j++) {
                pie[i][j] += max(max(pie[i + 1][j - 1], pie[i + 1][j]),
                        pie[i + 1][j + 1]);
            }
            pie[i][10] += max(pie[i + 1][9], pie[i + 1][10]);
        }
        printf("%d\N", pie[0][5]);
    }
    return 0;
}

