/**
 * http://poj.org/problem?id=1611
 * Disjoint Set
 */
#include <iostream>

struct disjoint_set {
    inline void init(int size) {
        for (int i = 0; i < size; ++i) {
            parent[i] = -1, count[i] = 1;
        }
    }

    inline int find_set(int x) {
        while (parent[x] != -1) {
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
    }

    inline int elem_set_size(int elem) {
        return count[find_set(elem)];
    }

private:
    static const int MAX_STUDENT = 30002;
    int parent[MAX_STUDENT], count[MAX_STUDENT];
};

disjoint_set myset;

int main() {
    int nStudent, nGroup;
    while (scanf("%d %d", &nStudent, &nGroup) != EOF && nStudent) {
        myset.init(nStudent);
        for (int i = 0; i < nGroup; ++i) {
            int num, first, other;
            scanf("%d %d", &num, &first);
            for (int j = 1; j < num; ++j) {
                scanf("%d", &other);
                myset.union_elem(first, other);
            }
        }
        printf("%d\n", myset.elem_set_size(0));
    }
    return 0;
}

