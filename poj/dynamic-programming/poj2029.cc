/**
 * POJ 2029, Get Many Persimmon Trees
 */
#include <cstdio>
#include <cstring>

const int MAX_LEN = 101;

inline int max(int a, int b) {
    return a > b ? a : b;
}

bool field[MAX_LEN][MAX_LEN];
int count[MAX_LEN][MAX_LEN];

int main() {
    int N, W, H; // num of persimmon trees, width and height of the whole land
    int x, y; // coordinate
    int S, T; // width and height of the given land
    while (scanf("%d", &N) != EOF && N) {
        scanf("%d %d", &W, &H);
        memset(field, false, sizeof(field));
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &y, &x);
            field[x - 1][y - 1] = true;
        }
        scanf("%d %d", &S, &T);

        memset(count, 0, sizeof(count));
        for (int i = 0; i + T <= H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = 0; k < T; ++k) {
                    count[i][j] += (field[i + k][j] ? 1 : 0);
                }
            }
        }

        int temp, curr, result = -1;
        for (int i = 0; i + T <= H; ++i) {
            curr = 0;
            for (int j = 0; j < S; ++j) {
                curr += count[i][j];
            }
            result = max(result, curr);
            for (int j = S; j < W; ++j) {
                temp = curr - count[i][j-S] + count[i][j];
                result = max(result, temp);
                curr = temp;
            }
        }

        printf("%d\n", result);
    }
    return 0;
}

