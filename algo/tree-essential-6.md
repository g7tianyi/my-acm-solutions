樹問題小結：二叉樹的對比問題
====

包括三類：

- 兩棵樹是否互為鏡像，或者創建一棵樹的鏡像
- 一棵樹是不是另一棵樹的拷貝
- 樹的同構問題，有根樹/無根樹

做一件事情，堅持到底TM難啊，樹的問題寫到這里，好累啊，說一個人要做的好，既要聰明又要勤奮，TM已經蠢得要死，勤奮TM好難做到啊，老天爺已經讓我又蠢且懶了， 還不讓我是個富二代官二代，靠！

##鏡像問題

###鏡像檢查

```C++
template<typename T>
bool is_mirror(tree_node<T>* tree1, tree_node<T>* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return true;
    }
    if (tree1 == NULL && tree2 != NULL) {
        return false;
    }
    if (tree1 != NULL && tree2 == NULL) {
        return false;
    }
    return tree1->value == tree2->value
            && is_mirror(tree1->left, tree2->right)
            && is_mirror(tree1->right, tree2->left);
}

/**
 * as always, simulate pre-order style traversing
 */
template<typename T>
bool is_mirror_iterative(tree_node<T>* tree1, tree_node<T>* tree2) {
    std::stack<tree_node<T>*> stack1, stack2;
    tree_node<T> *curr1 = tree1, *curr2 = tree2;

    while (curr1 || curr2 || !stack1.empty()) {
        while (curr1 || curr2) {
            if (curr1 == NULL && curr2 != NULL) {
                return false;
            }
            if (curr1 != NULL && curr2 == NULL) {
                return false;
            }
            if (curr1->value != curr2->value) {
                return false;
            }
            stack1.push(curr1);
            stack2.push(curr2);
            curr1 = curr1->left;
            curr2 = curr2->right;
        }
        if (!stack1.empty()) {
            curr1 = stack1.top();
            curr2 = stack2.top();
            stack1.pop();
            stack2.pop();
            curr1 = curr1->right;
            curr2 = curr2->left;
        }
    }

    return true;
}
```

###生成一棵樹的鏡像

還是樹的遍歷問題，所以左邊鏈接里的內容實在是太重要了。

年紀大＋懶＝直接貼代碼

```C++
// create mirror. recursion.
template<typename T>
tree_node <T>* create_mirror(tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }
    tree_node<T>* new_tree = new tree_node<T>(tree->value);
    new_tree->left = create_mirror(tree->right);
    new_tree->right = create_mirror(tree->left);
    return new_tree;
}

/**
 * create mirror. iteration.
 * consider if it is OK to implement is_mirror_iteratively in this way
 */
template<typename T>
tree_node <T>* create_mirror_iteratively(tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }

    tree_node <T>* newtree = new tree_node<T>(tree->value);

    std::deque<tree_node<T>*> oriqueue, newqueue;
    oriqueue.push_back(tree);
    newqueue.push_back(newtree);
    tree_node<T> *oricurr, *newcurr;
    while (!oriqueue.empty()) {
        oricurr = oriqueue.front();
        oriqueue.pop_front();
        newcurr = newqueue.front();
        newqueue.pop_front();

        if (oricurr->left) {
            newcurr->right = new tree_node<T>(oricurr->left->value);
            oriqueue.push_back(oricurr->left);
            newqueue.push_back(newcurr->right);
        }
        if (oricurr->right) {
            newcurr->left = new tree_node<T>(oricurr->right->value);
            oriqueue.push_back(oricurr->right);
            newqueue.push_back(newcurr->left);
        }
    }

    return newtree;
}
```

##一棵樹是不是另一棵樹的拷貝

LeetCode [Same Tree](https://oj.leetcode.com/problems/same-tree/)

```C++
template<typename T>
bool is_same_tree(tree_node<T>* tree1, tree_node<T>* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return true;
    }
    if (tree1 == NULL && tree2 != NULL) {
        return false;
    }
    if (tree1 != NULL && tree2 == NULL) {
        return false;
    }
    return tree1->value == tree2->value
            && is_same_tree(tree1->left, tree2->left)
            && is_same_tree(tree1->right, tree2->right);
}

template<typename T>
bool is_same_tree_iterative(tree_node<T>* tree1, tree_node<T>* tree2) {
    std::stack<tree_node<T>*> stack1, stack2;
    tree_node<T> *curr1 = tree1, *curr2 = tree2;

    while (curr1 || curr2 || !stack1.empty()) {
        while (curr1 || curr2) {
            if (curr1 == NULL && curr2 != NULL) {
                return false;
            }
            if (curr1 != NULL && curr2 == NULL) {
                return false;
            }
            if (curr1->value != curr2->value) {
                return false;
            }
            stack1.push(curr1);
            stack2.push(curr2);
            curr1 = curr1->left;
            curr2 = curr2->left;
        }
        if (!stack1.empty()) {
            curr1 = stack1.top();
            curr2 = stack2.top();
            stack1.pop();
            stack2.pop();
            curr1 = curr1->right;
            curr2 = curr2->right;
        }
    }

    return true;
}
```

##同構問題

*未完待續*
