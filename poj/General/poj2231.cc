/**
 * http://poj.org/problem?id=2231
 *
 * sort. discover the law of operation
 */

#include <cstdio>
#include <algorithm>

const int MAX_LEN = 10001;
long long arr[MAX_LEN];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld", &arr[i]);
    }

    std::sort(arr, arr + N);
    long long result = 0;
    for (int i = 0; i < N; ++i) {
        // arr[0].....arr[i]...arr[N-1]
        // for each arr[i], it contributes
        //  ( i * A[i] - (n - i - 1) * A[i] ) * 2
        // means it minus the previous i items
        // and get minused by the latter (n - i - 1) items
        result += (((i << 1) + 1 - N) * arr[i]);
    }
    printf("%lld", result << 1);
    return 0;
}

