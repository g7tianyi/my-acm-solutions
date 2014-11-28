/**
 * POJ 1125
 * dp + bfs, shortest path in graph
 */
#include <queue>
#include <cstdio>
#include <cstring>

static const int MAX_PEOPLE = 102;
static const int MAX_COST = 1000000000;

std::queue<int> queue;
bool flag[MAX_PEOPLE];
int cost[MAX_PEOPLE][MAX_PEOPLE];

int main() {

    int num, conn; // num of stockbrokers, num of connections

    while (scanf("%d", &num) != EOF && num) {

        memset(cost, -1, sizeof(cost));
        int i, j, k;
        for (i = 1; i <= num; ++i) {
            scanf("%d", &conn);
            for (j = 1; j <= conn; ++j) {
                scanf("%d", &k);
                scanf("%d", &cost[i][k]);
            }
        }

        for (i = 1; i <= num; ++i) {
            memset(flag, false, sizeof(flag));
            for (j = 1; j <= num; ++j) {
                if (cost[i][j] > 0) {
                    queue.push(j);
                    flag[j] = true;
                }
            }

            while (!queue.empty()) {
                j = queue.front();

                for (k = 1; k <= num; ++k) {
                    if (k == i || cost[j][k] < 0) {
                        continue;
                    }
                    if (cost[i][k] < 0
                            || cost[i][k] > cost[i][j] + cost[j][k]) {
                        cost[i][k] = cost[i][j] + cost[j][k];
                        if (!flag[k]) {
                            queue.push(k);
                            flag[k] = true;
                        }
                    }
                }

                flag[j] = false;
                queue.pop();
            }
        }

        bool available;
        int curr_cost, res_start, res_cost = MAX_COST;
        for (i = 1; i <= num; ++i) {
            curr_cost = -1;
            available = true;
            for (j = 1; j <= num; ++j) {
                if (i != j && cost[i][j] < 0) {
                    available = false;
                    break;
                }
                if (curr_cost < cost[i][j]) {
                    curr_cost = cost[i][j];
                }
            }

            if (available && res_cost > curr_cost) {
                res_cost = curr_cost;
                res_start = i;
            }
        }

        if (res_cost != MAX_COST) {
            printf("%d %d\n", res_start, res_cost);
        } else {
            printf("disjoint\n");
        }
    }

    return 0;
}

