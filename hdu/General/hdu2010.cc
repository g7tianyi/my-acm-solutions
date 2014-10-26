/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2010
 */
#include <cstdio>
#define CUBE(X) ((X) * (X) * (X))
int result[100];
int main() {
    int M, N;
    while (scanf("%d %d", &M, &N) != EOF) {
        int count = 0;
        for (int i = M; i <= N; ++i) {
            int num = i, sum = 0, r;
            while (num) {
                r = num % 10;
                sum += CUBE(r);
                num /= 10;
            }
            if (sum == i) {
                result[count++] = i;
            }
        }
        if (count) {
            for (int i = 0; i < count - 1; ++i) {
                printf("%d ", result[i]);
            }
            printf("%d\n", result[count - 1]);
        } else {
            printf("no\n");
        }
    }
    return 0;
}

