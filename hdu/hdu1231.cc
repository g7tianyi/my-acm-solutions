/**
 * HDU 1231, 最大连续子序列
 */
#include <cstdio>
#include <cstring>

const int MAX_N = 10001;
int N, arr[MAX_N];

int main() {
    while (scanf("%d", &N) != EOF && N) {
        int i;
        for (i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        int j = 0, curr = 0, max = -1;
        int start = 0, end = N - 1;
        for (i = 0; i < N; i++) {
            // result[i] = max { result[i-1] + arr[i], arr[i] }
            curr += arr[i];
            if (curr > max) {
                start = j;
                end = i;
                max = curr;
            } else if (curr < 0) {
                j = i + 1;
                curr = 0;
            }
        }
        if (max < 0) {
            max = 0;
        }
        printf("%d %d %d\n", max, arr[start], arr[end]);
    }
}

