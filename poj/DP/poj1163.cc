/**
 * POJ 1163 The Triangle
 * dp
 */
#include <cstdio>
#include <cstring>

const int MAX = 102;

int N;
int sums[2][MAX];

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {

    scanf("%d", &N);
    memset(sums, 0, sizeof(sums));

    int i, j, value;
    int row = 0;
    for (i = 0; i < N; ++i) {
        for (j = 0; j <= i; ++j) {
            scanf("%d", &value);
            // dp[i][j] = max { dp[i-1][j-1], dp[i-1][j] } + value[i][j]
            // also appling the sliding array here
            if (j > 0) {
                sums[1 - row][j] = max(sums[row][j - 1], sums[row][j]) + value;
            } else {
                sums[1 - row][j] = sums[row][j] + value;
            }
        }
        row = 1 - row;
    }

    int res = sums[row][0];
    for (i = 1; i < N; ++i) {
        if (res < sums[row][i]) {
            res = sums[row][i];
        }
    }
    printf("%d\n", res);

    return 0;
}

