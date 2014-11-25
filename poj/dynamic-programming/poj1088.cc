/**
 * POJ 1088
 * kinda of flood fill, memorized search (dp) in dfs
 */
#include <cstdio>
#include <cstring>

#define max(a, b) (a) > (b) ? (a) : (b)

static const int MIN_NUM = -1;
static const int MAX_LEN = 102;

int R, C;
int area[MAX_LEN][MAX_LEN];
int dp[MAX_LEN][MAX_LEN];
int result = -1;

// dp dfs
// dp[i][j] = max { dp[i - 1][j],  dp[i][j - 1], dp[i + 1][j], dp[i][j + 1] } + 1
void floodfill(int i, int j) {

    int len = 0;

    // try left
    if (area[i - 1][j] < area[i][j]) {
        if (dp[i - 1][j] < 0) {
            floodfill(i - 1, j);
        }
        len = max(len, dp[i - 1][j]);
    }

    // try top
    if (area[i][j - 1] < area[i][j]) {
        if (dp[i][j - 1] < 0) {
            floodfill(i, j - 1);
        }
        len = max(len, dp[i][j - 1]);
    }

    // try right
    if (area[i + 1][j] < area[i][j]) {
        if (dp[i + 1][j] < 0) {
            floodfill(i + 1, j);
        }
        len = max(len, dp[i + 1][j]);
    }

    // try bottom
    if (area[i][j + 1] < area[i][j]) {
        if (dp[i][j + 1] < 0) {
            floodfill(i, j + 1);
        }
        len = max(len, dp[i][j + 1]);
    }

    dp[i][j] = len + 1;

    //printf("dp[%d][%d] <- %d\n", i, j, dp[i][j]);

    if(result < dp[i][j]) {
        result = dp[i][j];
    }
}

int main() {

    memset(area, MIN_NUM, sizeof(area));
    memset(dp, 0, sizeof(dp));

    scanf("%d %d", &R, &C);

    // Area matrix would be,
    // -1 -1 -1 -1 -1 -1 -1
    // -1  1  2  3  4  5 -1
    // -1 16 17 18 19  6 -1
    // -1 15 24 25 20  7 -1
    // -1 14 23 22 21  8 -1
    // -1 13 12 11 10  9 -1
    // -1 -1 -1 -1 -1 -1 -1
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            scanf("%d", &area[i][j]);
            dp[i][j] = -1;
        }
    }

    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            if (dp[i][j] == -1) {
                floodfill(i, j);
            }
        }
    }

    printf("%d\n", result);

    return 0;
}


