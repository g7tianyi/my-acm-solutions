/**
 * HDU 1002, A + B Problem II.
 * DP. Max continuous subarray
 */
#include <cstdio>
#include <cstring>

const int MAX_N = 100001;

int arr[MAX_N];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
        }

        int max_all, max_start, max_end;
        int max_cur, cur_start, cur_end;
        max_all = max_cur = arr[0];
        max_start = cur_start = 1;
        max_end = cur_end = 1;
        for (int i = 1; i < N; ++i) {
            if (max_cur >= 0) {
                max_cur += arr[i];
                ++cur_end;
            } else {
                max_cur = arr[i];
                cur_start = i + 1;
                cur_end = i + 1;
            }
            if (max_all < max_cur) {
                max_all = max_cur;
                max_start = cur_start;
                max_end = cur_end;
            }
        }
        if (t > 1) {
            printf("\n");
        }
        printf("Case %d:\n", t);
        printf("%d %d %d\n", max_all, max_start, max_end);
    }

    return 0;
}

