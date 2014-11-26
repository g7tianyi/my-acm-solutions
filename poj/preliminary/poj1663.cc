/**
 * http://poj.org/problem?id=1663
 * Number Steps
 */

#include <iostream>

// pattern:
// denote dx/dy to be the difference of two adjacent coordinates
//
//  x  0  1  2  3  2  3  4  5  4 ...
//  y  0  1  0  1  2  3  2  3  4 ...
// dx     1  1  1 -1  1  1  1 -1 ...
// dy     1 -1  1  1  1 -1  1  1 ...
//
// during each cycle, both x and y increase 2
int factor[4][2] = {
    { 1, 1 }, // 2 * k + 1 = X, 2 * k + 1 = Y
    { 2, 0 }, // 2 * k + 2 = X, 2 * k + 0 = Y
    { 3, 1 }, // 2 * k + 3 = X, 2 * k + 1 = Y
    { 2, 2 }  // 2 * k + 2 = X, 2 * k + 2 = Y
};

int main() {
    int C, X, Y; // Cases, coordinate X and Y
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &X, &Y);
        bool cool = false;
        for (int i = 0, j; i < 4; ++i) {
            j = (X - factor[i][0]) >> 1;
            if ( (j << 1) == X - factor[i][0] &&
                    (j << 1) == Y - factor[i][1]) {
                printf("%d\n", (j << 2) + i + 1 );
                cool = true;
                break;
            }
        }
        if (!cool) {
            printf("No Number\n");
        }
    }
    return 0;
}

