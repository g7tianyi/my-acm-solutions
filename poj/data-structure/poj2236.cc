/**
 * http://poj.org/problem?id=2236
 * Wireless Network
 * 
 * union-find-set version. compare to the Graph modeling version.
 */

#include <iostream>

struct point {
    int x, y;
};

struct setelem {
    int father, fixed;
};

int N;
double D;
setelem setelems[1004];
bool graph[1004][1004];
point points[20002];

inline void make_set() {
    for (int i = 1; i <= N; ++i) {
        setelems[i].father = i;
        setelems[i].fixed = 0;
    }
}

inline int find(int a) {
    if (a != setelems[a].father) {
        setelems[a].father = find(setelems[a].father);
    }
    return setelems[a].father;
}

inline void union_set(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
        setelems[b].father = a;
    }
}

int main() {
    scanf("%d %lf", &N, &D);
    for (int i = 1; i <= N; ++i) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    memset(graph, false, sizeof(graph));
    for (int i = 1, j, k1, k2; i <= N; ++i) {
        for (j = i + 1; j <= N; ++j) {
            k1 = points[i].x - points[j].x;
            k2 = points[i].y - points[j].y;
            if (D * D >= k1 * k1 + k2 * k2) {
                graph[i][j] = graph[j][i] = true;
            }
        }
    }

    char operation[2];
    int a, b;
    make_set();
    while (scanf("%s", operation) != EOF && operation[0] != 'Q') {
        if (operation[0] == 'O') {
            scanf("%d", &a);
            setelems[a].fixed = 1;
            for (int i = 1; i <= N; ++i) {
                if (graph[a][i] && setelems[i].fixed) {
                    union_set(a, i);
                }
            }
        } else {
            scanf("%d %d", &a, &b);
            if (setelems[a].fixed && setelems[b].fixed && find(a) == find(b)) {
                printf("SUCCESS\n");
            } else {
                printf("FAIL\n");
            }
        }
    }

    return 0;
}

