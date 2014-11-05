樹問題小結：查找與刪除
====

#查找問題
----

分為兩類：

- 二叉搜索樹的查找
- 二叉隨機樹的查找

二叉搜索樹的查找很簡單，主要考慮怎麼樣用遞歸與非遞歸的方式實現。對於二叉隨機樹，其實就是樹的遍歷問題，DFS/BFS，我偷懶就用pre-order的思路實現了一下。

```C++
// find element in binary search tree, iterative style
template<typename T>
__tree_node <T>* find_elem_in_bst(__tree_node <T>* tree, const T& value) {
    __tree_node <T>* curr = tree;
    while (curr) {
        if (value == curr->value) {
            return curr;
        }
        if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}

// find element in binary search tree, recursive style
template<typename T>
__tree_node <T>* find_elem_in_bst_recursion(__tree_node <T>* tree, const T& value) {
    if (tree == NULL || value == tree->value) {
        return tree;
    }
    // rear recursion, good
    if (value < tree->value) {
        return find_elem_in_bst_recursion(tree->left, value);
    } else {
        return find_elem_in_bst_recursion(tree->right, value);
    }
}

// find element in binary random tree, iterative style
template<typename T>
__tree_node <T>* find_elem_in_brt(__tree_node <T>* tree, const T& value) {
    if (tree == NULL) {
        return NULL;
    }
    // it is just a tree traversing problem in iterative style
    // below is a pre-order traversing
    std::stack<__tree_node <T>*> stack;
    __tree_node <T>* curr = tree;
    while (curr || !stack.empty()) {
        while (curr) {
            if (value == curr->value) {
                return curr;
            }
            stack.push(curr);
            curr = curr->left;
        }
        if (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            curr = curr->right;
        }
    }
    return NULL;
}

// find element in binary search tree, recursive style
template<typename T>
__tree_node <T>* find_elem_in_brt_recursion(__tree_node <T>* tree, const T& value) {
    if (tree == NULL || value == tree->value) {
        return tree;
    }
    __tree_node <T>* result = find_elem_in_brt_recursion(tree->left, value);
    if (result) {
        return result;
    }
    return find_elem_in_brt_recursion(tree->right, value);
}
```

