/**
 * http://poj.org/problem?id=1218
 * THE DRUNK JAILER
 */

#include <iostream>

int arr[100];

int main() {
    int T, N;
    scanf("%d", &T);
    while (T--) {
        memset(arr, 0, sizeof(arr));
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (j % i == 0) {
                    arr[j] ^= 1;
                }
            }
        }
        int result = 0;
        for (int j = 1; j <= N; ++j) {
            result += arr[j];
        }
        printf("%d\n", result);
    }
    return 0;
}

