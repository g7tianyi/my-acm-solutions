/**
 * POJ 1975, Median Weight Bead
 * Warshall algorithm
 * The fancy part is tranforming the original problem into a graph problem
 */
#include <cstdio>
#include <cstring>

const int MAX_N = 100;
const char GT = 'L'; // greater than
const char LT = 'S'; // less than

char map[MAX_N][MAX_N];

int main() {
    int T, N, M;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        int large, small;
        memset(map, 0, sizeof(map));
        for (int i = 0; i < M; ++i) {
            scanf("%d %d", &large, &small);
            --large, --small;
            map[large][small] = GT;
            map[small][large] = LT;
        }

        // Warshall algorithm
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (!map[i][j]) {
                        if (map[i][k] == GT && map[k][j] == GT) {
                            map[i][j] = GT;
                        }
                        if (map[i][k] == LT && map[k][j] == LT) {
                            map[i][j] = LT;
                        }
                    }
                }
            }
        }

        int result = 0, half = (N + 1) >> 1, num_gt, num_lt;
        for (int i = 0; i < N; ++i) {
            num_gt = num_lt = 0;
            for (int j = 0; j < N; ++j) {
                if (map[i][j] == GT) {
                    ++num_gt;
                } else if (map[i][j] == LT) {
                    ++num_lt;
                }
            }
            if (num_gt >= half || num_lt >= half) {
                ++result;
            }
        }
        printf("%d\n", result);
    }

    return 0;
}

