/**
 * POJ 1276 Cash Machine
 * DP
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_DENO = 12, MAX_CASH = 100002
};

int CASH, DENO;
int value[MAX_DENO];
int count[MAX_DENO];
int F[MAX_DENO][MAX_CASH];

int main() {

    while (scanf("%d %d\n", &CASH, &DENO) != EOF) {

        memset(value, 0, sizeof(value));
        memset(count, 0, sizeof(count));

        for (int i = 1; i <= DENO; ++i) {
            scanf("%d %d\n", &count[i], &value[i]);
        }

        int v = 0;
        memset(F, 0, sizeof(F));
        for (int i = 1; i <= count[1]; ++i) {
            v = value[1] * i;
            if (v <= CASH) {
                F[1][v] = v;
            }
            printf("%d ", F[1][v]);
        }
        printf("\n");

        //
        // DP
        // F(i,j) = max { F(i-1, j - k * value(i)) + k * value(i) | 0 <= k <= count(i) }
        //
        // Optimations worth trying
        // 1) sliding array, 2-d array would suffice
        // 2) skiplist-like data structure for line (**)
        // 3) unnecessary of the loop (*)
        //
        for (int i = 2; i <= DENO; ++i) { // index of denominations
            for (int j = 1; j <= CASH; ++j) { // (*) value of cashes
                for (int k = 0; k <= count[i] && k * value[i] <= j; ++k) {
                    v = j - value[i] * k;
                    while (v > 0 && !F[i - 1][v]) { // (**)
                        --v;
                    }
                    if (F[i][j] < F[i - 1][v] + value[i] * k) {
                        F[i][j] = F[i - 1][v] + value[i] * k;
                    }
                }
            }
        }

        printf("%d\n", F[DENO][CASH]);
    }

    return 0;
}

