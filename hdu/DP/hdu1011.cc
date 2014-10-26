/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1011
 *
 * Tree DP.
 */
#include <vector>
#include <cstdio>
#include <cstring>

const int MAX_ROOM = 102;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int num_room, max_cost;
int cost[MAX_ROOM], value[MAX_ROOM];
std::vector<int> tree[MAX_ROOM];

bool visit[MAX_ROOM];
int dp[MAX_ROOM][MAX_ROOM];

void DFS(int curr) {
    visit[curr] = true;

    if (cost[curr] > max_cost) {
        return;
    }

    // DP(i, j), max value of assigning j cost to room i
    for (int j = cost[curr]; j <= max_cost; j++) {
        dp[curr][j] = value[curr];
    }

    int size = tree[curr].size();
    for (int i = 0; i < size; ++i) {
        int next = tree[curr][i];
        if (!visit[next]) {
            DFS(next);
            for (int j = max_cost; j >= cost[curr]; --j) {
                // curr should at least assign cost (ensure curr's bug can be omitted) => j - k >= cost
                for (int k = 0; k <= j - cost[curr]; ++k) {
                    // looks like range DP, ha..
                    dp[curr][j] = max(dp[curr][j], dp[curr][j - k] + dp[next][k]);
                }
            }
        }
    }

    // extreme case... >_<
    // W.T.F... no bugs in a room, but still got the chance to have a brain in it
    if (dp[curr][0] > 0) {
        dp[curr][1] = max(dp[curr][1], dp[curr][0]);
        dp[curr][0] = 0;
    }
}

int main() {
    while (scanf("%d %d", &num_room, &max_cost) != EOF && num_room != -1
            && max_cost != -1) {

        for (int i = 1; i <= num_room; i++) {
            scanf("%d %d", &cost[i], &value[i]);
            cost[i] = (cost[i] + 19) / 20;
        }

        for (int i = 0; i <= num_room; i++) {
            tree[i].clear();
        }
        for (int i = 1, x, y; i < num_room; i++) {
            scanf("%d %d", &x, &y);
            tree[x].push_back(y);
            tree[y].push_back(x);
        }

        if (max_cost == 0) {
            printf("0\n");
            continue;
        }

        memset(dp, 0, sizeof(dp));
        memset(visit, false, sizeof(visit));
        DFS(1);
        int result = 0;
        for (int i = 1; i <= max_cost; i++) {
            result = max(result, dp[1][i]);
        }
        printf("%d\n", result);
    }

    return 0;
}

