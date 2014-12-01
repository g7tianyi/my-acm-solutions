/**
 * http://poj.org/problem?id=2236
 * Wireless Network
 * Modeling by graph (DFS). TLE. 
 */

#include <algorithm>
#include <iostream>
#include <cmath>

struct point {
    int x, y;
};

inline double distance(const point& p1, const point& p2) {
    return sqrt((double) ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

int N;
double D;
bool state[1004]; // true => in service, false => out of service
bool graph[1004][1004];
bool visit[1004];
point points[20002];

bool dfs(int start, int end) {
    if (start == end) {
        return true;
    }
    for (int i = 1; i <= N; ++i) {
        if (graph[start][i] && state[i] && !visit[i]) {
            visit[i] = true;
            if (dfs(i, end)) {
                return true;
            }
            visit[i] = false;
        }
    }
    return false;
}

int main() {
    scanf("%d %lf", &N, &D);
    for (int i = 1; i <= N; ++i) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    memset(state, false, sizeof(state));
    memset(graph, false, sizeof(graph));
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (D >= distance(points[i], points[j])) {
                graph[i][j] = graph[j][i] = true;
            }
        }
    }

    char operation[2];
    int a, b;
    while (scanf("%s", operation) != EOF && operation[0] != 'Q') {
        if (operation[0] == 'O') {
            scanf("%d", &a);
            state[a] = true;
        } else {
            scanf("%d %d", &a, &b);
            memset(visit, false, sizeof(visit));
            visit[a] = true;
            printf("%s\n", dfs(a, b) ? "SUCCESS" : "FAIL");
        }
    }

    return 0;
}

