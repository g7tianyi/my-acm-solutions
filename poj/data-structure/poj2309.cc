/**
 * http://poj.org/problem?id=2309
 *
 * BST.
 *
 * binary search tree property. good problem~
 */

#include <iostream>

inline int log2(int num) {
    int k = 0;
    while (num) {
        num >>= 1;
        ++k;
    }
    return k - 1;
}

int main() {
    int T, num;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &num);
        int first, last;
        if ((num & (num - 1)) == 0) { // if it is power of 2
            first = 1, last = (num << 1) - 1;
        } else {
            int k = log2(num), mid;
            first = (1 << k) + 1;
            last  = (1 << (k + 1)) - 1;
            while (true) { // binary search
                mid = first + ((last - first) >> 1);
                if (mid == num) {
                    break;
                } else if (mid > num) {
                    last = mid - 1;
                } else {
                    first = mid + 1;
                }
            }
        }
        printf("%d %d\n", first, last);
    }
    return 0;
}

