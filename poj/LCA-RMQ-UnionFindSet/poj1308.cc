/**
 * http://poj.org/problem?id=1308
 * Is it a Tree ?
 * Union-Find Set
 */

#include <cstdio>

const int MAX_NODE = 128;

int father[MAX_NODE];
bool visit[MAX_NODE];

void make_set() {
    for (int i = 0; i < MAX_NODE; ++i) {
        father[i] = i;
        visit[i] = false;
    }
}

int find_set(int x) {
    if (x != father[x]) {
        father[x] = find_set(father[x]);
    }
    return father[x];
}

void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        father[y] = x;
    }
}

int main() {
    int cases = 0, x, y;
    while (scanf("%d %d", &x, &y) != EOF) {
        if (x == -1 && y == -1) {
            break;
        }
        if (x == 0 && y == 0) { // empty tree.. faint...
            printf("Case %d is a tree.\n", ++cases);
            continue;
        }

        make_set();
        int tag = x;
        visit[x] = visit[y] = true;
        bool valid = true;
        if (find_set(x) == find_set(y)) {
            valid = false;
        } else {
            union_set(x, y);
        }

        while (scanf("%d %d", &x, &y) && x && y) {
            visit[x] = visit[y] = true;
            if (find_set(x) == find_set(y)) {
                valid = false;
            } else {
                union_set(x, y);
            }
        }

        for (int i = 1; i < MAX_NODE; i++) {
            // can not be a forest
            if (visit[i] && find_set(i) != find_set(tag)) {
                // means exists more than two trees
                valid = false;
            }
        }

        if (valid) {
            printf("Case %d is a tree.\n", ++cases);
        } else {
            printf("Case %d is not a tree.\n", ++cases);
        }
    }

    return 0;
}

