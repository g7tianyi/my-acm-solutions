/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1561
 *
 * Tree DP.
 */
#include <vector>
#include <cstdio>
#include <cstring>

enum {
    MAX_CASTLE = 202, MAX_BATTLE = 202
};

inline int max(int a, int b) {
    return a > b ? a : b;
}

int nCastle, nBattle;
int value[MAX_CASTLE];
std::vector<int> tree[MAX_CASTLE];

bool visit[MAX_CASTLE];
int dp[MAX_CASTLE][MAX_BATTLE];

void DFS(int curr) {
    visit[curr] = true;

    int size = tree[curr].size();
    for (int i = 0; i < size; ++i) { // try all subtree
        int next = tree[curr][i];
        if (!visit[next]) {
            DFS(next);
            for (int j = nBattle; j > 0; --j) { // conquering j castles in subtree curr
                // make sure the parent node has been conquered => k != j
                for (int k = 0; k < (curr == 0 ? j + 1 : j); ++k) { // conquering k castles in subtree next
                    dp[curr][j] = max(dp[curr][j],
                            dp[curr][j - k] + dp[next][k]);
                }
                //printf("dp[%d][%d]=%d\t", curr, j, dp[curr][j]);
            }
            //printf("\n");
        }
    }
}

int main() {
    while (scanf("%d %d", &nCastle, &nBattle) != EOF && (nCastle || nBattle)) {

        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= nCastle; ++i) {
            tree[i].clear();
        }

        for (int i = 1, parent; i <= nCastle; ++i) {
            scanf("%d %d", &parent, &value[i]);
            tree[parent].push_back(i);
            dp[i][1] = value[i];
        }

        memset(visit, false, sizeof(visit));
        DFS(0);
        printf("%d\n", dp[0][nBattle]);
    }

    return 0;
}

