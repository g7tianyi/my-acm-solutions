/**
 * URAL 1001, Reverse Root
 */
#include <cmath>
#include <cstdio>

// 256 * 1024 / sizeof(long)
double input[1000000];

int main() {
    int i = 0, j;
    while (scanf("%lf", &input[i]) != EOF) {
        i++;
    }
    for (j = i - 1; j >= 0; j--) {
        printf("%.4lf\n", sqrt(input[j]));
    }
    return 0;
}

