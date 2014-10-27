/**
 * http://poj.org/problem?id=2388
 */

#include <cstdio>
#include <algorithm>

static const int MAX_N = 1 << 14;
static int arr[MAX_N];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }
    std::sort(arr, arr + N);
    printf("%d\n", arr[N >> 1]);
    return 0;
}

