/**
 * http://poj.org/problem?id=1470
 *
 * LCA. Tarjan algo.
 */

#include <vector>
#include <cstdio>
#include <cstring>

const int MAX_NODE = 901;

std::vector<int> trees[MAX_NODE];
std::vector<int> query[MAX_NODE];

bool visited[MAX_NODE];
int set_root[MAX_NODE];
int set_rank[MAX_NODE];
int ancestor[MAX_NODE];

int result[MAX_NODE];

void init(int size) {
    memset(visited, false, sizeof(visited));
    memset(ancestor, 0, sizeof(ancestor));
    memset(result, 0, sizeof(result));
    for (int i = 1; i <= size; i++) {
        set_rank[i] = 1;
        set_root[i] = i;
        trees[i].clear();
        query[i].clear();
    }
}

int find_set(int x) {
    if (set_root[x] != x) {
        set_root[x] = find_set(set_root[x]);
    }
    return set_root[x];
}

void union_elem(int x, int y) {
    int set_x = find_set(x), set_y = find_set(y);
    if (set_x == set_y) {
        return;
    }
    if (set_rank[set_x] < set_rank[set_y]) {
        set_root[set_x] = set_y;
    } else {
        set_root[set_y] = set_x;
        set_rank[set_x] += (set_rank[set_x] == set_rank[set_y]);
    }
}

void tarjan(int curr) {
    ancestor[curr] = curr;
    int size = trees[curr].size();
    for (int i = 0; i < size; ++i) { // try every subtree
        tarjan(trees[curr][i]);
        union_elem(curr, trees[curr][i]);
        // all subtree's predecessor are curr
        ancestor[find_set(curr)] = curr;
    }

    // all of curr's sub node have been visited
    visited[curr] = true;
    for (int i = 0; i < query[curr].size(); ++i) {
        if (visited[query[curr][i]]) {
            ++result[ancestor[find_set(query[curr][i])]];
        }
    }
}

int main() {
    int num_node;
    while (scanf("%d", &num_node) != EOF) {

        init(num_node);

        int root, count, succ;
        for (int i = 0; i < num_node; ++i) {
            scanf("%d:(%d)", &root, &count);
            for (int j = 0; j < count; ++j) {
                scanf("%d", &succ);
                trees[root].push_back(succ);
                visited[succ] = true;
            }
        }

        scanf("%d", &count);
        int node1, node2;
        for (int i = 0; i < count; ++i) {
            while(getchar() != '(') ; // stupid input
            scanf("%d %d", &node1, &node2);
            query[node1].push_back(node2);
            query[node2].push_back(node1);
            while(getchar() != ')') ; // stupid input
        }

        // find the root
        root = -1;
        for (int i = 1; i <= num_node; ++i) {
            if (!visited[i]) {
                root = i;
                break;
            }
        }

        memset(visited, false, sizeof(visited));
        tarjan(root);
        for (int i = 1; i <= num_node; ++i) {
            if (result[i]) {
                printf("%d:%d\n", i, result[i]);
            }
        }

    }
    return 0;
}

