/*
 ID: fairyroad1106
 LANG: C++
 TASK: numtri
 */
#include <cstdio>

#ifdef LOCAL_MODE
#define PROGID "input"
#else
#define PROGID "numtri"
#endif
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

int m[1000][1000];
int value[1000];
inline int max(const int a, const int b) {
    return a > b ? a : b;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i + 1; ++j) {
            scanf("%d", &m[i][j]);
        }
    }

    for (i = 0; i < n; ++i) {
        value[i] = m[n - 1][i];
    }

    for (i = n - 2; i >= 0; --i) {
        for (j = 0; j < i + 1; ++j) {
            value[j] = m[i][j] + max(value[j], value[j + 1]);
        }
    }
    printf("%d\n", value[0]);

    return 0;
}

