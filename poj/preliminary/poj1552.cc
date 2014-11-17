/**
 * http://poj.org/problem?id=1552
 */

#include <iostream>

int arr[16];

int main() {
    while (true) {
        scanf("%d", &arr[0]);
        if (arr[0] == -1) {
            break;
        }
        int i = 1;
        while (scanf("%d", &arr[i]) != EOF && arr[i]) {
            ++i;
        }
        // data volume is too small, just looping all over them
        // for big data set, binary search or hash should be very helpful
        int result = 0;
        for (int j = 0, twice; j < i; ++j) {
            twice = arr[j] << 1;
            for (int k = 0; k < i; ++ k) {
                if (arr[k] == twice) {
                    ++result;
                    break;
                }
            }
        }
        printf("%d\n", result);
    }
    return 0;
}

