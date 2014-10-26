/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2544
 * Shortest path. Dijkstra algo.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_NODE = 102,
    INF_MAX = 99999999
};

int num_node, num_edge;
int graph[MAX_NODE][MAX_NODE];
int value[MAX_NODE];
bool visit[MAX_NODE];

int dijkstra(int start, int target) {
    // value[i] denotes the min cost from start to i
    for (int i = 1; i <= num_node; ++i) {
        value[i] = graph[start][i];
    }
    graph[start][start] = 0;

    memset(visit, false, sizeof(visit));
    visit[start] = true;

    for (int i = 1; i <= num_node; ++i) {
        int nextmin = INF_MAX, next = -1;
        // find the next node with min value so far
        // can be optimized with priority_queue
        for (int j = 1; j <= num_node; ++j) {
            if (!visit[j] && nextmin > value[j]) {
                next = j, nextmin = value[j];
            }
        }

        if (nextmin == INF_MAX) {
            break;
        }
        visit[next] = true;

        for (int j = 1; j <= num_node; ++j) {
            // Per CLRS, this is the so called - "RELAX"
            if (!visit[j] && value[j] > value[next] + graph[next][j]) {
                value[j] = value[next] + graph[next][j];
            }
        }
    }

    return value[target];
}

int main() {
    int start, end, cost;
    while (scanf("%d %d", &num_node, &num_edge) && (num_node || num_edge)) {
        for (int i = 1; i <= num_node; ++i) {
            for (int j = 1; j <= num_node; ++j) {
                graph[i][j] = INF_MAX;
            }
        }
        for (int i = 0; i < num_edge; ++i) {
            scanf("%d %d %d", &start, &end, &cost);
            if (graph[start][end] > cost) {
                graph[start][end] = graph[end][start] = cost;
            }
        }
        printf("%d\n", dijkstra(1, num_node));
    }

    return 0;
}

