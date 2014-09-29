/**
 * HDU 1505, City Game
 * DP. transform to 1-d problem
 */
#include <cstdio>
#include <cstring>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

enum {
    MAX_LEN = 1001, UNIT_COST = 3
};

bool map[MAX_LEN][MAX_LEN];
bool dp[MAX_LEN][MAX_LEN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int height, width;
        scanf("%d %d", &height, &width);
        char buf[2];
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                scanf("%s", buf);
                dp[i][j] = map[i][j] = (buf[0] == 'F');
            }
        }

        int maxarea = 0, currsum;
        for (int k = 0; k < height; ++k) { // height
            for (int i = 0; i < height - k; ++i) { // row
                currsum = 0;
                for (int j = 0; j < width; ++j) { // column
                    // dp[i][j] in the left is the status of height i
                    // while the right means the status for height i-1
                    dp[i][j] = dp[i][j] && map[i + k][j];
                    currsum = dp[i][j] ? currsum + 1 : 0;
                    maxarea = MAX(maxarea, currsum * (k + 1));
                }
            }
        }

        printf("%d\n", UNIT_COST * maxarea);
    }

    return 0;
}

