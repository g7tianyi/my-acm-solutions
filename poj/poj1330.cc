/**
 * http://poj.org/problem?id=1330
 *
 * LCA, very classical.
 */
#include<cstring>
#include<cstdio>
#include<vector>

const int MAX_NODE = 10002;

bool visited[MAX_NODE];
std::vector<int> tree[MAX_NODE];

int set_root[MAX_NODE]; // union set's root
int set_rank[MAX_NODE]; // union set's rank

int query1, query2;
int predecessor[MAX_NODE];

void init(int size) {
    memset(visited, false, sizeof(visited));
    memset(predecessor, 0, sizeof(predecessor));
    for (int i = 1; i <= size; i++) {
        set_rank[i] = 1;
        set_root[i] = i;
        tree[i].clear();
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
        set_rank[set_y] += set_rank[set_x];
    } else {
        set_root[set_y] = set_x;
        set_rank[set_x] += set_rank[set_y];
    }
}

bool tarjan(int curr) {
    predecessor[curr] = curr;
    int size = tree[curr].size();
    for (int i = 0; i < size; ++i) { // try every subtree
        if (tarjan(tree[curr][i])) {
            return true;
        }
        union_elem(curr, tree[curr][i]);
        // all subtree's predecessor are curr
        predecessor[find_set(curr)] = curr;
    }

    // all of curr's sub node have been visited
    visited[curr] = true;
    if (visited[query1] && visited[query2]) {
        printf("%d\n",
                curr == query1 ? predecessor[find_set(query2)] : predecessor[find_set(query1)]);
        return true;
    }

    return false;
}

int main() {
    int cases, num_node;
    scanf("%d", &cases);
    for (int c = 0; c < cases; ++c) {

        scanf("%d", &num_node);
        init(num_node);
        int i, j, k;
        for (k = 0; k < num_node - 1; ++k) {
            scanf("%d %d", &i, &j);
            tree[i].push_back(j);
            visited[j] = true;
        }

        // find tree root
        int root = -1;
        for (k = 1; k <= num_node; k++) {
            if (!visited[k]) {
                root = k;
                break;
            }
        }

        memset(visited, false, sizeof(visited));
        scanf("%d %d", &query1, &query2);
        tarjan(root);
    }

    return 0;
}

