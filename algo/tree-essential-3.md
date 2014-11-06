樹問題小結：樹的節點統計、樹的深度
====

#節點統計問題

根據節點類型分為兩類：

- 統計葉子節點的數量
- 統計所有節點的數量

首先，如果我們知道樹的一些別的信息，也許就能直接算出答案了：

- 已知樹是一個滿二叉樹，且高度H已知，那麼就可以套公式：

    * 葉子節點：2 ^ (H - 1)
    * 所有節點：2 ^ H - 1

其次，涉及樹的問題，基本都是遞歸的思路，而我覺得真正掌握了樹的遍歷，那麼樹的絕大多數問題都不是大問題，比如節點統計問題。

##編程實現
```C++
template<typename T>
unsigned count_leaf_node(tree_node <T>* tree) {
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
unsigned count_all_node(tree_node <T>* tree) {
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
unsigned min_depth(tree_node <T>* tree) {
    if (tree == NULL) {
        return 0;
    }

    std::deque<tree_node <T>*> queue;
    queue.push_back(tree), queue.push_back(NULL);
    unsigned depth = 1;
    while (!queue.empty()) {
        tree_node <T>* curr = queue.front();
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
unsigned max_depth(tree_node <T>* tree) {
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
unsigned max_depth_iteration(tree_node <T>* tree) {
    std::stack<tree_node <T>*> node_stack;
    std::stack<unsigned> depth_stack;
    tree_node <T>* curr = tree;
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

// test below

typedef tree::default_value_type value_type;

tree::tree_node<value_type>* __test_create_tree(std::vector<value_type>& vec,
        tree::binary_tree_type treeType) {
    if (treeType == tree::BINARY_RANDOM_TREE) {
        return tree::create_tree(vec.begin(), vec.end());
    } else {
        tree::binary_search_tree_optioner<value_type> bst_picker;
        return tree::create_tree(vec.begin(), vec.end(), bst_picker);
    }
}

int main() {

    const int TEST_DATA_SIZE = 97;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value());
    }

    tree::tree_node<value_type>* tree = __test_create_tree(vec,
            tree::BINARY_RANDOM_TREE);

    std::cout << tree::max_depth(tree) << std::endl;
    std::cout << tree::max_depth_iteration(tree) << std::endl;

    tree::release_tree(tree);

    return 0;
}
```
