/**
 * HDU 1001, Sum Problem.
 * discretion is virtue
 */
#include <cstdio>
int main() {
    int n, flag = 0;
    while (scanf("%d", &n) != EOF) {
        if (n & 0x1u) { // odd number, n * (n + 1) may exceed INT_MAX
            printf("%d\n\n", n * ((n + 1) >> 1));
        } else {
            printf("%d\n\n", (n >> 1) * (1 + n));
        }

    }
    return 0;
}

