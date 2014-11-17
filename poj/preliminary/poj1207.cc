/**
 * http://poj.org/problem?id=1207
 */

#include <iostream>

int main() {
    int first, last;
    while (scanf("%d %d", &first, &last) != EOF) {
        int beg, end;
        if (first > last) {
            beg = last, end = first;
        } else {
            beg = first, end = last;
        }

        int res = 1, len, num;
        for (int i = beg; i <= end; ++i) {
            len = 1, num = i;
            while (num != 1) {
                if (num & 0x1u) {
                    num = num * 3 + 1;
                } else {
                    num >>= 1;
                }
                ++len;
            }
            res = len > res ? len : res;
        }
        printf("%d %d %d\n", first, last, res);
    }
    return 0;
}

