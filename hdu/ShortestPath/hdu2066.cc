/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2544
 *
 * Shortest path. Dijkstra algo.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_NODE = 1002, INF_MAX = 99999999
};

int graph[MAX_NODE][MAX_NODE];
int value[MAX_NODE];
bool visit[MAX_NODE];

int num_node;
int starts[MAX_NODE];
int ends[MAX_NODE];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

/**
 * Get the shortest path from start to all nodes in the graph
 */
void dijkstra(int start) {
    // value[i] denotes the min cost from start to i
    for (int i = 1; i <= num_node; ++i) {
        value[i] = graph[start][i];
    }
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
}

int main() {
    int T, S, D;
    while (scanf("%d %d %d", &T, &S, &D) != EOF) {
        for (int i = 0; i < MAX_NODE; ++i) {
            for (int j = 0; j < MAX_NODE; ++j) {
                graph[i][j] = (i != j ? INF_MAX : 0);
            }
        }

        num_node = -1;
        int a, b, cost;
        for (int i = 0; i < T; ++i) {
            scanf("%d %d %d", &a, &b, &cost);
            if (graph[a][b] > cost) {
                graph[a][b] = graph[b][a] = cost;
            }
            num_node = max(num_node, max(a, b));
        }

        for (int i = 0; i < S; ++i) {
            scanf("%d", &starts[i]);
        }

        for (int i = 0; i < D; ++i) {
            scanf("%d", &ends[i]);
        }

        int result = INF_MAX;
        for (int i = 0; i < S; ++i) {
            dijkstra(starts[i]);
            for (int j = 0; j < D; ++j) {
                result = min(result, value[ends[j]]);
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

