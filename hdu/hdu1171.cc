/**
 * HDU 1171, Big Event in HDU
 * http://acm.hdu.edu.cn/showproblem.php?pid=1171
 *
 * multiple-packing problem
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_ITEM  = 52 * 8,  // 7 =>「log(50)」
    MAX_VALUE = 1250010, // 50 * 50 * 1000 / 2
};
int value[MAX_ITEM], dp[MAX_VALUE];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N > 0) {
        int sum = 0, i = 0, j = 0, k, val, cnt;
        for (; i < N; ++i) {
            scanf("%d %d", &val, &cnt);
            sum += (val * cnt);
            k = 1;
            while (k <= cnt) {
                value[j++] = val * k;
                k <<= 1;
            }
            k >>= 1;
            if (k < cnt) {
                value[j++] = val * (cnt - k);
            }
        }

        cnt = j;
        int half = (sum + 1) >> 1;
        memset(dp, 0, sizeof(dp));
        for (i = 0; i < cnt; ++i) {
            for (j = half; j >= value[i]; --j) {
                dp[j] = max(dp[j], dp[j - value[i]] + value[i]);
            }
        }
        if (dp[half] * 2 > sum) {
            printf("%d %d\n", dp[half], sum - dp[half]);
        } else {
            printf("%d %d\n", sum - dp[half], dp[half]);
        }
    }
    return 0;
}

