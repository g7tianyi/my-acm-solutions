/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1166
 *
 * segment tree
 */
#include <cstdio>
#include <cstring>

struct segnode {
    int left;
    int right;
    int count;
};
int count[50010];

struct segtree {
    segnode node[50010 << 2];

    void init(int left, int right, int index) {
        node[index].left = left;
        node[index].right = right;

        if (left == right) {
            node[index].count = count[left];
            return;
        }

        int middle = median(left, right);
        init(left, middle, left_son(index));
        init(middle + 1, right, right_son(index));
        node[index].count = node[left_son(index)].count
                + node[right_son(index)].count;
    }

    /**
     * Update the target_node with adding/subtracting delta
     */
    void update(int target_index, int delta) {
        update(1, target_index, delta);
    }

    /**
     * Query the interval [left, right]
     */
    int query(int left, int right) {
        return query(left, right, 1);
    }

private:
    void update(int curr_index, int target_index, int delta) {
        int left = node[curr_index].left;
        int right = node[curr_index].right;
        int middle = median(left, right);

        if (target_index == left && target_index == right) {
            node[curr_index].count += delta;
            return;
        }

        if (target_index > middle) {
            update(right_son(curr_index), target_index, delta);
        } else {
            update(left_son(curr_index), target_index, delta);
        }
        node[curr_index].count += delta;
    }

    int query(int left, int right, int index) {
        if (node[index].left == left && node[index].right == right) {
            return node[index].count;
        }
        if (node[index].left == node[index].right) {
            return 0;
        }

        int middle = median(node[index].left, node[index].right);
        if (right <= middle) {
            return query(left, right, left_son(index));
        } else if (left > middle) {
            return query(left, right, right_son(index));
        } else {
            return query(left, middle, left_son(index))
                    + query(middle + 1, right, right_son(index));
        }
    }

private:
    inline int left_son(int curr) {
        return curr << 1;
    }
    inline int right_son(int curr) {
        return (curr << 1) + 1;
    }
    inline int median(int left, int right) {
        return left + ((right - left) >> 1);
    }
};

segtree tree;

int main() {
    char command[10];

    int T;
    scanf("%d", &T);
    for (int t = 1, N; t <= T; ++t) {
        printf("Case %d:\n", t);
        scanf("%d", &N);
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &count[j]);
        }
        tree.init(1, N, 1);

        int x, y;
        while (scanf("%s", command) != EOF && command[0] != 'E') {
            scanf("%d %d", &x, &y);
            if (command[0] == 'Q') { // query
                printf("%d\n", tree.query(x, y));
            } else if (command[0] == 'A') { // add
                tree.update(x, y);
            } else {
                tree.update(x, -y);
            }
        }
    }

    return 0;
}

