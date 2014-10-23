/**
 * http://poj.org/problem?id=2524
 * Disjoint Set
 */
#include <iostream>

struct disjoint_set {
    inline void init(int size) {
        group = size;
        for (int i = 1; i <= size; ++i) {
            parent[i] = i, count[i] = 1;
        }
    }

    inline int find_set(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    inline void union_elem(int a, int b) {
        int set1 = find_set(a), set2 = find_set(b);
        if (set1 == set2) {
            return;
        }
        if (count[set1] < count[set2]) {
            parent[set1] = set2;
            count[set2] += count[set1];
        } else {
            parent[set2] = set1;
            count[set1] += count[set2];
        }
        --group;
    }

    inline int groups() {
        return group;
    }

private:
    static const int MAX_STUDENT = 50002;
    int parent[MAX_STUDENT], count[MAX_STUDENT];
    int group;
};

disjoint_set myset;

int main() {
    int nStudent, nPair, cases = 1;
    while (scanf("%d %d", &nStudent, &nPair) != EOF && nStudent) {
        myset.init(nStudent);
        int p1, p2;
        for (int i = 0; i < nPair; ++i) {
            scanf("%d %d", &p1, &p2);
            myset.union_elem(p1, p2);
        }
        printf("Case %d: %d\n", cases++, myset.groups());
    }
    return 0;
}

