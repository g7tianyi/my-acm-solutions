/**
 * http://poj.org/problem?id=2190
 * ISBN
 */

#include <iostream>

char buf[12];

int main() {
    scanf("%s", buf);

    int num = 0, fac, pos;
    for (int i = 0, j = 10; i < 10; ++i, --j) {
        if (buf[i] == '?') {
            pos = i, fac = j;
        } else if (buf[i] == 'X') {
            num += (10 * j);
        } else {
            num += ((buf[i] - '0') * j);
        }
    }

    int result = -1;
    for (int i = 0; i < (pos == 9 ? 11 : 10); ++i) {
        if ((num + i * fac) % 11 == 0) {
            result = i;
            break;
        }
    }
    if (result == 10) {
        printf("X\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}

