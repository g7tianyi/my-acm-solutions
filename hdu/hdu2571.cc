/**
 * HDU 2571, 命运
 * http://acm.hdu.edu.cn/showproblem.php?pid=2571
 * DFS Version
 */
#include <cstdio>
#include <cstring>

const int MAX_ROW = 22;
const int MAX_COLUMN = 1002;
const int INIFINTE = 2147483648;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int N, M;
int maze[MAX_ROW][MAX_COLUMN], dp[MAX_ROW][MAX_COLUMN];

int DFS(int x, int y) {
    if (x == N && y == M) {
        return maze[x][y];
    }
    if (dp[x][y] != INIFINTE) {
        return dp[x][y] ;
    }

    int result = -INIFINTE;
    if (x + 1 <= N) { // go down
        result = max(result, DFS(x + 1, y));
    }
    if (y + 1 <= M) { // go right
        result = max(result, DFS(x, y + 1));
    }
    int k = 2;
    while (k * y <= M) { // skip right
        result = max(result, DFS(x, k * y));
        ++k;
    }
    dp[x][y] = result + maze[x][y];
    return dp[x][y];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                scanf("%d", &maze[i][j]);
                dp[i][j] = INIFINTE;
            }
        }
    }
    DFS(1, 1);
    printf("%d\n", dp[1][1]);
    return 0;
}

