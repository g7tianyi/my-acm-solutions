/**
 * http://poj.org/problem?id=2387
 *
 * Shortest path. Dijkstra algo.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_LAND = 2001, // landmark
    INF_MAX = 99999999
};

int graph[MAX_LAND][MAX_LAND];
int cost[MAX_LAND];
bool visit[MAX_LAND];

int dijkstra(int start, int target) {
    graph[start][start] = 0;
    // cost(i) denotes the minimum cost from source node to i
    for (int i = 1; i <= start; ++i) {
        cost[i] = graph[start][i];
    }

    memset(visit, false, sizeof(visit));
    visit[start] = true;

    for (int i = 1; i < start; ++i) {
        int nextmin = INF_MAX, next = -1;
        // find the next node with min cost so far
        // can be optimized with priority_queue
        for (int j = 1; j <= start; ++j) {
            if (!visit[j] && cost[j] != -1 && nextmin > cost[j]) {
                next = j, nextmin = cost[j];
            }
        }

        visit[next] = true;
        for (int j = 1; j <= start; ++j) {
            // Per CLRS, this is the so called - "RELAX"
            if (!visit[j] && graph[next][j] != -1 // not visited and 'next' can reach 'j'
                    && (cost[j] == -1 || cost[j] > cost[next] + graph[next][j])) {
                cost[j] = cost[next] + graph[next][j];
            }
        }
    }

    return cost[target];
}

int main() {
    int T, N;
    scanf("%d %d", &T, &N);
    memset(graph, -1, sizeof(graph));
    int a, b, length;
    for (int i = 0; i < T; ++i) {
        scanf("%d %d %d", &a, &b, &length);
        if (graph[a][b] == -1 || graph[a][b] > length) {
            graph[a][b] = graph[b][a] = length;
        }
    }
    printf("%d\n", dijkstra(N, 1));
    return 0;
}

