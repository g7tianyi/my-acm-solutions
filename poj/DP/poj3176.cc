/**
 * http://poj.org/problem?id=3176
 *
 * DP.
 */

#include <cstdio>
#include <cstring>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int MAX_N = 352;
int number[MAX_N][MAX_N];

int main() {
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
            if (j) {
                number[i][j] += MAX(number[i - 1][j - 1], number[i - 1][j]);
            } else {
                number[i][j] += number[i - 1][j];
            }
        }
    }

    int result = number[N - 1][0];
    for (int i = 1; i < N; ++i) {
        result = MAX(result, number[N - 1][i]);
    }
    printf("%d\n", result);

    return 0;
}

