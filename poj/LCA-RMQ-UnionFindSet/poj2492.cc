/**
 * http://poj.org/problem?id=2492
 *
 * A Bug's Life
 *
 * Union-find-set.
 *
 * Compare it with poj 1141
 */

#include <cstdio>

int const MAX_BUG = 2002;

// Union-find-set
//
// parent[x] indicates the parent of x
// relation[x] indicates the relationship with the representive of the set
//
// if two bugs have relationship with each other, they are joinned into the
// same set
// for elements in the same set, e.g.
//     figure 1
//        A         #) A is the representive of this set
//     /  |  \      #) A and B1, B2, B3 are normal relationship
//    B1  B2  B3    #) B1 and C1, B3 and C3 are normal relationship
//    |        \    #) But, A and C1,C3 share abnormal relationship
//    C1       C3   #) We will see this logic propagation in find()
//
int parent[MAX_BUG];
// relation[i] indicates the relationship between i and the representive of the set
// 0 for normal, 1 for abnormal
int relation[MAX_BUG];

inline void init_set(int size) {
    for (int i = 1; i <= size; ++i) {
        parent[i] = i;
        relation[i] = 0;
    }
}
int find_set(int x) {
    if (x == parent[x]) {
        return x;
    }
    int p = parent[x];
    parent[x] = find_set(parent[x]);
    // check figure 1
    relation[x] ^= relation[p];
    return parent[x];
}
void union_set(int x, int y) {
    int setx = find_set(x);
    int sety = find_set(y);
    parent[setx] = sety;
    // R is the representive of the set
    // (a,b) is the relationship between a and b
    // (x,R) (y,R) => (x,y)
    //   0     0        1
    //   0     1        0
    //   1     0        0
    //   1     1        1
    relation[setx] = !(relation[x] ^ relation[y]);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        int num, rel;
        scanf("%d %d", &num, &rel);

        init_set(num);

        int x, y;
        bool suspicious = false;
        while (rel--) {
            scanf("%d %d", &x, &y);
            // x and y are assumed to normal relation
            if (find_set(x) == find_set(y)) {
                // #) x and y are in the same set
                // #) R is the representive of the set
                // #) (x,R) (y,R) => (x,y)
                //      0     0        1
                //      1     1        1
                suspicious = suspicious || (relation[x] == relation[y]);
            } else {
                union_set(x, y);
            }
        }

        printf("Scenario #%d:\n", i);
        if (suspicious) {
            printf("Suspicious bugs found!\n");
        } else {
            printf("No suspicious bugs found!\n");
        }
        printf("\n");
    }
    return 0;
}

