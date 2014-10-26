/**
 * http://poj.org/problem?id=2421
 *
 * MST. prime algo.
 */
#include<cstring>
#include<cstdio>

enum {
    MAX_VILLAGE = 105, INF_MAX = 9999 // [0, 1000]
};

int cost[MAX_VILLAGE][MAX_VILLAGE];
int queue[MAX_VILLAGE];
bool visited[MAX_VILLAGE];

int prim(int nVertex) {
    int result = 0;

    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= nVertex; i++) {
        queue[i] = INF_MAX;
    }
    queue[1] = 0;

    // One optimization here is counting the node whose adjacency's cost are not INF_MAX
    for (int i = 1; i <= nVertex; ++i) {
        int min = -1;
        for (int j = 1; j <= nVertex; ++j) {
            // pick up the edge with minimum cost
            // can be optimized by implementing the queue to be a heap
            if (!visited[j] && (min == -1 || queue[min] > queue[j])) {
                min = j;
            }
        }

        result += queue[min];
        visited[min] = true;

        // update next by min's adjacent node
        for (int j = 1; j <= nVertex; ++j) {
            if (!visited[j] && cost[min][j] != -1 && queue[j] > cost[min][j]) {
                queue[j] = cost[min][j];
            }
        }
    }

    return result;
}

int main() {

    int num_vill, num_road;
    scanf("%d", &num_vill);
    memset(cost, -1, sizeof(cost));

    for (int i = 1; i <= num_vill; ++i) {
        for (int j = 1; j <= num_vill; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    scanf("%d", &num_road);
    for (int i = 0, v1, v2; i < num_road; ++i) {
        scanf("%d%d", &v1, &v2); // village 1 and village 2
        cost[v1][v2] = 0;
        cost[v2][v1] = 0;
    }

    printf("%d\n", prim(num_vill));
    return 0;
}

