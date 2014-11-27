/**
 * http://poj.org/problem?id=3258
 *
 * River Hopscotch
 *
 * binary seach. good.
 */

#include <cstdio>
#include <algorithm>

const int MAX_ROCK = 50002;

// length. num of all rocks. num of rocks that can be removed
int L, N, M;
int arr[MAX_ROCK];

bool legal(int mid) {
    int j = 0, count = 0;
    for (int i = 1; i <= N + 1; ++i) {
        if (arr[i] - arr[j] <= mid) {
            ++count;
        } else {
            j = i;
        }
    }
    return count <= M;
}

int main() {
    while (scanf("%d %d %d", &L, &N, &M) != EOF) {
        arr[0] = 0, arr[N + 1] = L;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        std::sort(arr, arr + N + 2);
        int left = 0, right = L, mid;
        // try all possible minimum jump by binary search
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            if (legal(mid)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        printf("%d\n", left);
    }
    return 0;
}


