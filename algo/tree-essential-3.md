樹問題小結：樹的節點統計、樹的深度
====

#節點統計問題

根據節點類型分為兩類：

- 統計葉子節點的數量
- 統計所有節點的數量

----------

首先，如果我們知道樹的一些別的信息，也許就能直接算出答案了：

- 已知樹是一個滿二叉樹，且高度H已知，那麼就可以套公式：

    * 葉子節點：2^(H - 1)
    * 所有節點：2^H - 1

其次，涉及樹的問題，基本都是遞歸的思路，而我覺得真正掌握了樹的遍歷，那麼樹的絕大多數問題都不是大問題，比如節點統計問題。

##編程實現
```C++
template<typename T>
unsigned count_leaf_node(__tree_node <T>* tree) {
    if (tree) {
        if (tree->left == NULL && tree->right == NULL) {
            return 1;
        } else {
            return count_leaf_node(tree->left) + count_leaf_node(tree->right);
        }
    }
    return 0;
}

template<typename T>
unsigned count_all_node(__tree_node <T>* tree) {
    if (tree) {
        return count_all_node(tree->left) + count_all_node(tree->right) + 1;
    }
    return 0;
}
```

#深度問題
----
LeetCode [minimum depth](https://oj.leetcode.com/problems/minimum-depth-of-binary-tree/), [maximum depth](https://oj.leetcode.com/problems/maximum-depth-of-binary-tree/)

真沒啥好說的。

```C++
template<typename T>
unsigned min_depth(__tree_node <T>* tree) {
    if (tree == NULL) {
        return 0;
    }

    std::deque<__tree_node <T>*> queue;
    queue.push_back(tree), queue.push_back(NULL);
    unsigned depth = 1;
    while (!queue.empty()) {
        __tree_node <T>* curr = queue.fron();
        queue.pop_front();

        if (curr) {
            if (curr->left == NULL && curr->right == NULL) {
                break;
            }
            if (curr->left) {
                queue.push_back(curr->left);
            }
            if (curr->right) {
                queue.push_back(curr->right);
            }
        } else {
            if (!queue.empty()) {
                ++depth;
                queue.push_back(NULL);
            }
        }
    }
    return depth;
}

// if we need to implement max_depth in iterative style
// 1) try BFS
// 2) simulate recursion with stack
template<typename T>
unsigned max_depth(__tree_node <T>* tree) {
    if (tree == NULL) {
        return 0;
    }
    unsigned max_left = tree->left ? max_depth(tree->left) : 0;
    unsigned max_right = tree->right ? max_depth(tree->right) : 0;
    return std::max(max_left, max_right) + 1;
}

// iterative style of max_depth
// simulate in-order traverse
template<typename T>
unsigned max_depth_iteration(__tree_node <T>* tree) {
    std::stack<__tree_node<T>*> node_stack;
    std::stack<unsigned> depth_stack;
    __tree_node <T>* curr = tree;
    int depth = 1, result = 0;
    while (curr || !node_stack.empty()) {
        while (curr) {
            node_stack.push(curr);
            depth_stack.push(depth);
            curr = curr->left;
            ++depth;
        }
        if (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            depth = depth_stack.top();
            depth_stack.pop();

            result = std::max(result, depth);
            curr = curr->right;
            ++depth;
        }
    }
    return result;
}
```
