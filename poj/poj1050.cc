/**
 * POJ 1050 To the Max
 * dp
 * convert 2-d problem into 1-d
 * O(n^3)
 */
#include <cstdio>
#include <cstring>

static const int MIN_SUM = 0xFFFFFFFF;
static const int MAX_LEN = 101;

int matrix[MAX_LEN][MAX_LEN];
int array[MAX_LEN];

int main() {
    int N;
    scanf("%d", &N);

    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // max_arr, max sum of the whole array so far
    // max_end, max sum ending in k
    int result = MIN_SUM, max_arr, max_end, k;
    for (i = 0; i < N; ++i) {
        memset(array, 0, sizeof(array));
        for (j = i; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                array[k] += matrix[j][k];
            }
            max_arr = max_end = array[0];
            for (k = 1; k < N; ++k) {
                max_end = max_end > 0 ? max_end + array[k] : array[k];
                if (max_arr < max_end) {
                    max_arr = max_end;
                }
            }
            if (result < max_arr) {
                result = max_arr;
            }

        }
    }

    printf("%d\n", result);

    return 0;
}

