/**
 * http://poj.org/problem?id=2215
 * sounds like dynamic programming..
 */

#include <iostream>

// grid[i][j], sum of rectangle (0, 0, i, j)
int grid[1001][1001];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int row, col;
        scanf("%d %d", &row, &col);

        int num;
        for (int i = 1; i <= row; ++i) {
            for (int j = 1; j <= col; ++j) {
                scanf("%d", &num);
                grid[i][j] = num + grid[i][j - 1] + grid[i - 1][j] - grid[i - 1][j - 1];
            }
        }

        int query, r1, s1, r2, s2;
        scanf("%d", &query);
        while (query--) {
            scanf("%d %d %d %d", &r1, &s1, &r2, &s2);
            num = (grid[r2][s2] + grid[r1 - 1][s1 - 1])
                    - (grid[r1 - 1][s2] + grid[r2][s1 - 1]);
            printf("Absolutni hodnota pohodlnosti je %d bodu.\n", num);
        }
        printf("\n");
    }
    return 0;
}

