/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2022
 */
#include <cstdio>

#define ABS(X) ((X) > 0 ? (X) : -(X))

int main() {
    int M, N;
    while (scanf("%d %d", &M, &N) != EOF) {
        int res_i = -1, res_j, res, val;
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &val);
                if (res_i == -1 || (ABS(res) < ABS(val))) {
                    res = val, res_i = i, res_j = j;
                }
            }
        }
        printf("%d %d %d\n", res_i, res_j, res);
    }
    return 0;
}

