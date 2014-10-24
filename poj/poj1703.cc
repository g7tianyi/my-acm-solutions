/**
 * http://poj.org/problem?id=1703
 */
#include <iostream>

const int MAX_CRIMINAL = 100002;

int root[MAX_CRIMINAL]; // i.e., father.
int gang[MAX_CRIMINAL]; // 0: in the same gang as its root, 1 for different

inline void make_set(int size) {
    for (int i = 1; i <= size; ++i) {
        root[i] = i;
        gang[i] = 0; // share the same gang with itself of course
    }
}

inline int find_set(int x) {
    if (x == root[x]) {
        return x;
    }
    int p = root[x]; // parent node of x
    root[x] = find_set(root[x]);
    // x  p
    // 1  0  => 1
    // 0  1  => 1
    // 1  1  => 0
    // 0  0  => 0
    gang[x] ^= gang[p];
    return root[x];
}

inline void union_elem(int x, int y) {
    int rx = find_set(x), ry = find_set(y);
    root[rx] = ry;
    // relation(rx, ry) <=
    //   relation(rx, x) + relation(x, y) + relation(y, ry)
    //   since relation(x, y) will always be 1 (doesn't belong to the same gang)
    //   rx  x   y  ry
    //   G   S   G   S   => 1
    //   S   S   G   S   => 0
    //   G   S   G   G   => 0
    //   S   S   G   G   => 1
    //   ...
    gang[rx] = (gang[x] == gang[y]);
}

int main() {
    int T;
    int n, m;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%*c", &n, &m);
        make_set(n);

        char c;
        int x, y;
        while (m--) {
            scanf("%c%d%d%*c", &c, &x, &y);
            if (c == 'A') {
                if (find_set(x) == find_set(y)) {
                    if (gang[x] != gang[y]) {
                        printf("In different gangs.\n");
                    } else {
                        printf("In the same gang.\n");
                    }
                } else {
                    printf("Not sure yet.\n");
                }
            } else if (c == 'D') {
                union_elem(x, y);
            }
        }
    }
    return 0;
}

