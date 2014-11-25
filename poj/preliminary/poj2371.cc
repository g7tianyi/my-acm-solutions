/**
 * http://poj.org/problem?id=2371
 * Questions and answers
 */

#include <algorithm>
#include <iostream>

int arr[100002];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }
    std::sort(arr, arr + N);
    char buf[16];
    scanf("%s", buf);

    int Q, num;
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d", &num);
        printf("%d\n", arr[num - 1]);
    }
    return 0;
}

