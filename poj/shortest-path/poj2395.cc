/**
 * http://poj.org/problem?id=2395
 * Out of Hay
 * Kruskal. union find set.
 */

#include <algorithm>
#include <iostream>

enum {
    MAX_VERTEX = 2002,
    MAX_EDGE   = 2000 * 2000
};

////////////////////////////////////////
struct UnionSet {
public:
    inline void init(int size) {
        for (int i = 0; i < size; ++i) {
            father[i] = i;
        }
    }

    int find_set(int a) {
        if (a != father[a]) {
            father[a] = find_set(father[a]);
        }
        return father[a];
    }

    inline void unite_set(int a, int b) {
        a = find_set(a), b = find_set(b);
        if (a != b) {
            father[a] = b;
        }
    }

    inline bool same_set(int a, int b) {
        return find_set(a) == find_set(b);
    }

private:
    int father[MAX_VERTEX];
};

////////////////////////////////////////
struct Edge {
    int u, v;
    int cost;
};
inline bool operator<(const Edge& edge1, const Edge& edge2) {
    return edge1.cost < edge2.cost;
}

UnionSet unionSet;
Edge edges[MAX_EDGE];
int V, E;

int kruskal() {
    std::sort(edges, edges + E);
    unionSet.init(V);
    int result = 0;
    for (int i = 0; i < E; ++i) {
        Edge edge = edges[i];
        if (!unionSet.same_set(edge.u, edge.v)) {
            unionSet.unite_set(edge.u, edge.v);
            result = std::max(result, edge.cost);
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
    }
    printf("%d\n", kruskal());
    return 0;
}

