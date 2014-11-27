/**
 * POJ 1961, Period
 * KMP
 */
#include<cstdio>

char buf[1000005];
int fail[1000005];

int main() {
    int N, CASES = 1;
    while (scanf("%d", &N), N) {
        printf("Test case #%d\n", CASES++);
        scanf("%s", buf);
        fail[0] = -1;
        for (int i = 1, j = -1; i < N; i++) {
            while (j >= 0 && buf[i] != buf[j + 1]) {
                // backtracking pointer j
                j = fail[j];
            }
            if (buf[i] == buf[j + 1]) {
                ++j;
            }
            fail[i] = j;
            if ((j + 1 >= (i + 1) / 2)
                    && ((i + 1) % (i - j) == 0)) {
                printf("%d %d\n", i + 1, (i + 1) / (i - j));
            }
        }
        printf("\n");
    }
    return 0;
}
