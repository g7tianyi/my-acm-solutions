/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1874
 *
 * Shortest path
 * 1) Dijkstra algo should be the fastest algo
 * 2) Try floyd here
 */

#include <cstdio>

enum {
    MAX_NODE = 202,
    INF_MAX = 99999999
};

int num_vill, num_road; // N, M
int graph[MAX_NODE][MAX_NODE];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int floyd(int start, int end) {
   for (int k = 0; k < num_vill; ++k) {
       for (int i = 0; i < num_vill; ++i) {
           for (int j = 0; j < num_vill; ++j) {
               graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
           }
       }
   }
   if (graph[start][end] < INF_MAX) {
       return graph[start][end];
   } else {
       return -1;
   }
}

int main() {
    int start, end;
    while (scanf("%d %d", &num_vill, &num_road) != EOF) {
        for (int i = 0; i < MAX_NODE; ++i) {
            for (int j = 0; j < MAX_NODE; ++j) {
                graph[i][j] = (i != j ? INF_MAX : 0);
            }
        }
        int a, b, length;
        for (int i = 0; i < num_road; ++i) {
            scanf("%d %d %d", &a, &b, &length);
            if (graph[a][b] > length) {
                // bidirectional paths
                graph[a][b] = graph[b][a] = length;
            }
        }
        scanf("%d %d", &start, &end);
        printf("%d\n", floyd(start, end));
    }
    return 0;
}

