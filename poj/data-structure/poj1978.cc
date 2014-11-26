/**
 * http://poj.org/problem?id=1978
 * Hanafuda Shuffle
 */

#include <iostream>

int arr[64];
int tmp[64];

int main() {
    int M, R;
    while (scanf("%d %d", &M, &R) != EOF && (M || R)) {
        int i = 0, j = M;
        while (i < M) {
            arr[i++] = j--;
        }
        while (R--) {
            scanf("%d %d", &i, &j);
            --i;
            // how about using a list here ?
            memcpy (tmp, arr + i, sizeof(int) * j);
            memmove(arr + j, arr, sizeof(int) * i);
            memcpy (arr, tmp,     sizeof(int) * j);
        }
        printf("%d\n", *arr);
    }
    return 0;
}

