/**
 * POJ 1609 Tiling Up Blocks
 * DP
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_BLOCKS 10002

struct BLOCK {
    int left, mid;
};

inline bool comp(BLOCK& block1, BLOCK& block2) {
    if (block1.left != block2.left) {
        return block1.left < block2.left;
    }
    return block1.mid < block2.mid;
}

BLOCK blocks[MAX_BLOCKS];
int dp[MAX_BLOCKS];

int main() {

    int N;
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &blocks[i].left, &blocks[i].mid);
        }
        std::sort(blocks, blocks + N, comp);

        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int tmp, result = 0;
        for (int i = 1; i < N; ++i) {
            tmp = 0; // arbitarily initialize to -1 at the first try, receive WA, >_<
            for (int j = i - 1; j >= 0; --j) {
                if (tmp < dp[j] && blocks[j].mid <= blocks[i].mid ) {
                    tmp = dp[j];
                }
            }
            dp[i] = tmp + 1;
            if (result < dp[i]) {
                result = dp[i];
            }
        }

        printf("%d\n", result);
    }

    printf("*");

    return 0;
}

