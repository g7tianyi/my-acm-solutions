/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1879
 * MST, standard Kruskal algo.
 */

#include <algorithm>
#include <cstdio>

enum {
    MAX_VERTEX = 100, MAX_EDGE = 5051
};

struct EDGE {
    int begin, end, cost;
};
EDGE edge[MAX_EDGE];

int parent[MAX_VERTEX]; // for union-find set

inline bool edge_comp(const EDGE& edge1, const EDGE& edge2) {
    return edge1.cost < edge2.cost;
}

void init_set(int size) {
    for (int i = 0; i <= size; ++i) {
        parent[i] = i;
    }
}

int find_set(int curr) {
    int root = curr;
    // find the label (representive) of the set which curr belongs to
    while (root != parent[root]) {
        root = parent[root];
    }
    // now pare is curr set label
    // compress the path, assign the parent of every node in the path
    // from curr to pare to be pare
    int pred; // means predecessor
    while (curr != root) {
        pred = parent[curr];
        parent[curr] = root;
        curr = pred;
    }
    return root;
}

int kruskal(int num_vertex, int num_edge) {
    std::sort(edge, edge + num_edge, edge_comp);
    init_set(num_vertex);
    int edge_count = 0, result = 0;
    for (int i = 0; i < num_edge; ++i) {
        int begin_set = find_set(edge[i].begin);
        int end_set = find_set(edge[i].end);
        if (begin_set != end_set) {
            parent[begin_set] = end_set;
            result += edge[i].cost;
            if (++edge_count == num_vertex - 1) {
                break;
            }
        }
    }
    return result;
}

int main() {
    int num_vill, num_road;
    while (scanf("%d", &num_vill) != EOF && num_vill) {
        num_road = (num_vill * (num_vill - 1)) >> 1;
        int exist;
        for (int i = 0; i < num_road; ++i) {
            scanf("%d %d %d %d", &edge[i].begin, &edge[i].end, &edge[i].cost, &exist);
            if (edge[i].begin > edge[i].end) {
                std::swap(edge[i].begin, edge[i].end);
            }
            if (exist) {
                edge[i].cost = 0;
            }
        }
        printf("%d\n", kruskal(num_vill, num_road));
    }
    return 0;
}

