樹問題小結：其他
====

##二叉樹中任意兩節點的最低公共祖先

- 如果兩個節點分別在根節點的左子樹和右子樹，則返回根節點
- 如果兩個節點都在左子樹，則遞歸處理左子樹
- 如果兩個節點都在右子樹，則遞歸處理右子樹

這種辦法好理解但是效率很低，很多搜索是重複的，所以直接優化就是記錄搜索路徑，見下面的代碼。

```C++
template<typename T>
bool exists_node(tree_node<T>* tree, tree_node<T>* node) {
    if (tree == NULL || node == NULL) {
        return false;
    }
    if (tree == node) {
        return true;
    }
    return tree == node
            || exists_node(tree->left, node)
            || exists_node(tree->right, node);
}

// very inefficienct
template<typename T>
tree_node<T>* least_common_ancestor(tree_node<T>* tree, tree_node<T>* node1,
        tree_node<T>* node2) {
    if (exists_node(tree->left, node1)) {
        if (exists_node(tree->right, node2)) {
            return tree;
        } else {
            return least_common_ancestor(tree->left, node1, node2);
        }
    } else {
        if (exists_node(tree->left, node2)) {
            return tree;
        } else {
            return least_common_ancestor(tree->right, node1, node2);
        }
    }
}

template<typename T>
bool get_node_path(tree_node<T>* tree, tree_node<T>* node,
        std::deque<tree_node<T>*> path) {
    if (tree == node) {
        path.push_back(tree);
    }
    if (tree == NULL) {
        return false;
    }
    path.push_back(tree);
    bool found = get_node_path(tree->left, node, path);
    if (!found) {
        found = get_node_path(tree->right, node, path);
    }
    if (!found) {
        path.pop_back();
    }
    return found;
}

template<typename T>
tree_node<T>* least_common_ancestor_iteration(tree_node<T>* tree, tree_node<T>* node1,
        tree_node<T>* node2) {
    if (tree == NULL || node1 == NULL || node2 == NULL) {
        return NULL;
    }
    std::deque<tree_node<T>*> path1;
    bool found1 = get_node_path(tree, node1, path1);
    std::deque<tree_node<T>*> path2;
    bool found2 = get_node_path(tree, node2, path2);
    if (!found1 || !found2) {
        return NULL;
    }

    tree_node<T>* result = tree;
    std::deque<tree_node<T>*>::const_iterator pos1 = path1.begin();
    std::deque<tree_node<T>*>::const_iterator pos2 = path2.begin();
    while (pos1 != path1.end() && pos2 != path2.end()) {
        if (*pos1 == *pos2) {
            result = *pos1;
        } else {
            break;
        }
        ++pos1, ++pos2;
    }

    return result;
}
```

##二叉樹中節點的最大距離

兩個情況：

- 路徑經過左子樹的最深節點，通過根節點，再到右子樹的最深節點
- 路徑不穿過根節點，而是左子樹或右子樹的最大距離路徑中的最值

```C++
// get the max distance of two node in a tree
template<typename T>
void max_distance(tree_node<T>* tree, int& distance, int& depth) {
    if (tree == NULL) {
        distance = 0, depth = -1;
        return;
    }

    int left_max_distance = 0;
    int left_max_depth = 0;
    max_distance(tree->left, left_max_distance, left_max_depth);

    int right_max_distance = 0;
    int right_max_depth = 0;
    max_distance(tree->right, right_max_distance, right_max_depth);

    depth = std::max(left_max_depth, right_max_depth) + 1;
    distance = std::max(std::max(left_max_distance, right_max_distance),
            left_max_depth + right_max_depth + 2);
}

template<typename T>
int max_distance(tree_node<T>* tree) {
    int distance = 0, depth = 0;
    max_distance(tree, distance, depth);
    return distance;
}
```

##判斷二叉樹是不是完全二叉樹

> In a complete binary tree, every level except possibly the last, is completely filled, and all nodes are as far left as possible. 

層序遍历。

當遇到一個節點的左子樹為空時，則該節點右子樹必須為空，且从此以往，遍歷的節點左右子樹都必須為空，否則不是完全二叉樹。

所以TM還是基礎要紮實，樹的基本問題中，80%都是遍歷的問題。

```C++
// check is a tree is a complete binary tree
template<typename T>
bool is_complete_tree(tree_node<T>* tree) {
    if (tree == NULL) {
        return false;
    }

    std::deque<tree_node<T>*> queue;
    queue.push_back(tree);

    bool should_be_leaf = false;
    bool result = true;

    while (!queue.empty()) {
        tree_node<T>* node = queue.front();
        queue.pop_front();

        if (should_be_leaf) {
            if (node->left || node->right) {
                result = false;
                break;
            }
        } else {
            if (node->left && node->right) {
                queue.push_back(node->left);
                queue.push_back(node->right);
            } else if (node->left && !node->right) {
                should_be_leaf = true;
                queue.push(node->left);
            } else if (!node->left && node->right) {
                result = false;
                break;
            } else {
                should_be_leaf = true;
            }
        }
    }

    return result;
}
```
