/**
 * HDU 2084, 数塔
 */
#include <cstdio>
#include <cstring>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int MAX_N = 128;
int number[MAX_N][MAX_N];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int N;
        scanf("%d", &N);
        memset(number, 0, sizeof(number));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                scanf("%d", &number[i][j]);
            }
        }
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (j > 0) {
                    number[i][j] += MAX(number[i - 1][j - 1], number[i - 1][j]);
                } else {
                    number[i][j] += number[i - 1][j];
                }
            }
        }
        int result = -1;
        for (int j = 0; j < N; ++j) {
            result = MAX(result, number[N - 1][j]);
        }
        printf("%d\n", result);
    }
    return 0;
}

