/*
 ID: fairyroad1106
 PROG: ariprog
 LANG: C++
 */
#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

#define PROGID "ariprog"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

bool flag[125001];

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    int i, j;
    for (i = 0; i <= M; i++) {
        for (j = 0; j <= M; j++) {
            flag[i * i + j * j] = true;
        }
    }

    bool found, NONE = true;
    for (j = 1; j <= 2 * M * M / (N - 1); j++) {
        for (i = 0; i + (N - 1) * j <= 2 * M * M; i++) {
            found = true;
            for (int k = 0; k < N; k++) {
                if (!flag[i + k * j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                printf("%d %d\n", i, j);
                NONE = false;
            }
        }
    }

    if (NONE) {
        printf("NONE\n");
    }

    return 0;
}

