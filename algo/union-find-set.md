訓練題
---
> POJ [2492](http://poj.org/problem?id=2492) 邪惡的好題

并查集的實現模板
---
```C++
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
    static const int MAX_NODE = 10000;
    int parent[MAX_NODE], count[MAX_NODE];
};
```

