/**
 * POJ 1189
 * Will WA. I can not find the bug of this code.
 */
#include <cstdio>
#include <cstring>

typedef unsigned long long MyLong;

const int MAX_N = 60;

int N, M;
char board[MAX_N][MAX_N];
MyLong dp[MAX_N][MAX_N * 2];

inline MyLong gcd(MyLong a, MyLong b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    MyLong tmp;
    if (a < b) {
        tmp = a;
        a = b;
        b = tmp;
    }
    while (b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {

    scanf("%d %d\n", &N, &M);

    int i, j, k;
    for (i = 0; i < N; ++i) {
        j = 0;
        while ((k = fgetc(stdin)) != '\n') {
            if (k != ' ') {
                board[i][j++] = (char) k;
            }
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0] = (1L << N);

    MyLong tmp;
    for (i = 0; i <= N; ++i) {
        for (j = 0; j < 2 * i + 1; ++j) {
            if (j & 0x1u) { // a slot position
                dp[i + 1][j + 1] += dp[i][j];
            } else {  // a nail position
                k = (j >> 1);
                if (board[i][k] == '*') {
                    tmp = (dp[i][j] >> 1);
                    dp[i + 1][2 * k]     += tmp;
                    dp[i + 1][2 * k + 2] += tmp;
                } else {
                    dp[i + 1][2 * k + 1] += dp[i][j];
                }
            }
        }
    }

    MyLong d = gcd(dp[N][M * 2], dp[0][0]);
    if (d) {
        printf("%lld/%lld\n", dp[N][M * 2] / d, dp[0][0] / d);
    } else {
        printf("%d/%lld\n", 0, dp[0][0]);
    }

    return 0;
}

