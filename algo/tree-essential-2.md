樹問題小結：前驅與後繼、最小值與最大值
====

#前驅與後繼問題
----

前驅與後繼問題其實實踐意義很大。首先，實現二叉搜索樹的刪除操作時，我們就需要找到當前節點的前驅來替換當前節點。此外，有一類實時查詢問題，需要找到與當前值差值最小的值（比如時序數據），如果數據是用二叉搜索樹建模的，那麼這個查詢就是查找前驅與後繼。

嚴謹的討論中，前驅與後繼也包含三類，即：

- 前序前驅，前序後繼
- 中序前驅，中序後繼
- 後序前驅，後序後繼

而實踐中，中序前驅/後繼價值更大一些，這是因為中序遍歷一個二叉搜索樹能到是整個樹的有序排序。後面我會先實現中序前驅/後繼的算法，其他兩類先只總結一下其算法過程，以後有時間在實現之。

##中序前驅，中序後繼

### 前驅

- 如有左孩子，前驅是左孩子的最右下節點
- 若無左孩子，且是父母的右孩子，則前驅就是父母；若無左孩子，且是父母的左孩子，則一直上溯到第一個“右祖先”則前驅就是這個祖先
- 若無這樣的祖先，說明該節點沒有前驅

### 後繼

- 如有右孩子，後繼是右孩子的最左下節點
- 若無右孩子，且是父母的左孩子，則後繼就是父母；若無右孩子，且是父母的右孩子，則一直上溯到第一個“左祖先”則後繼就是這個祖先
- 若無這樣的祖先，說明該節點沒有後繼

###編程實現

```C++
//
// in theory, predecessor and successor also has 3 types:
//  1) pre-order predecessor and successor
//  2) in-order predecessor and successor
//  3) post-order predecessor and successor
// in practical, in-order predecessor and successor is of highest value
// since the deletion operation depends on it
//


// find the predecessor of the specified value
// the value must be in the tree, otherwise we return NULL
template<typename T>
__tree_node <T>* predecessor_in_bst(__tree_node <T>* tree, const T& value) {
    __tree_node <T>* curr = tree; // curr and parent pointer
    std::deque<__tree_node <T>*> ancestors;
    ancestors.push_back(NULL);
    while (curr) {
        if (value == curr->value) {
            break;
        }
        ancestors.push_back(curr);
        if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr == NULL) { // value not exists in the tree
        return NULL;
    }

    // 1) if curr has a left child, the rightmost child of curr's left child is the predecessor
    // 2) otherwise, we trace back to the root, the first right ancestor is the predecessor
    // 3) if no such ancestor exists, then curr has no predecessor
    if (curr->left) {
        // has left child
        curr = curr->left;
        while (curr->right) {
            curr = curr->right;
        }
        return curr;
    } else {
        // has no left child
        __tree_node <T>* parent = ancestors.back();
        ancestors.pop_back();
        while (parent && parent->right != curr) {
            curr = parent;
            parent = ancestors.back();
            ancestors.pop_back();
        }
        return parent;
    }
}

// find the successor of the specified value
// the value must be in the tree, otherwise we return NULL
template<typename T>
__tree_node <T>* successor_in_bst(__tree_node <T>* tree, const T& value) {
    __tree_node <T>* curr = tree; // curr and parent pointer
    std::deque<__tree_node <T>*> ancestors;
    ancestors.push_back(NULL);
    while (curr) {
        if (value == curr->value) {
            break;
        }
        ancestors.push_back(curr);
        if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr == NULL) { // value not exists in the tree
        return NULL;
    }

    // 1) if curr has a right child, the leftmost child of curr's right child is the successor
    // 2) otherwise, we trace back to the root, the first left ancestor is the successor
    // 3) if no such ancestor exists, then curr has no successor
    if (curr->right) {
        curr = curr->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    } else {
        __tree_node <T>* parent = ancestors.back();
        ancestors.pop_back();
        while (parent && parent->left != curr) {
            curr = parent;
            parent = ancestors.back();
            ancestors.pop_back();
        }
        return parent;
    }
}
```

## 前序前驅，前序後繼

###前驅

- 若是父母的左孩子，則前驅是父母
- 若是父母的右孩子，且父母無左子樹，則前驅是父母
- 若是父母的右孩子，父母有左子樹，則前驅是父母左子樹的最後訪問到的節點（指向父母的左子樹後，一直往右，若不行的話，往左一步，一直到葉子）

###後繼

- 若有左孩子，則後繼就是左孩子
- 若无左孩子，有右孩子，则后继是右孩子
- 若既无左孩子，又无右孩子，即該節點為葉子節點，那麼：
 1. 若該節點是其父母的左孩子，且父母有右孩子，则后继是父母的右孩子
 2. 若該節點是其父母的左孩子，且父母無右孩子，或者該節點是其父母的右孩子，說明該節點是某個節點的左子樹是前序遍歷的最後一個節點，則需要找第一個有右子樹的“左祖先”，然後後繼就是這個祖先的右孩子

## 後序前驅，後序後繼

###前驅

- 若有右孩子，則前驅是右孩子；
- 若無右孩子，有左孩子，則前驅是左孩子；
- 若既無左孩子，又無右孩子，則是一片葉子，那麼：
  1. 若是其父母的右孩子，且父母有左孩子，則前驅是父母的左孩子
  2. 若是其父母的右孩子，且父母無左孩子，或者該節點其父母的左孩子，說明該節點是某個節點的右子樹後序遍歷的第一個節點，則需要找第一個有左子樹的“右祖先”，然後前驅就是這個祖先的左孩子

###後繼

- 若是父母的右孩子，則後繼是父母
- 若是父母的左孩子，且父母無右子樹，則後繼是父母
- 若是父母的左孩子，父母有右子樹，則後繼是父母右子樹的最先訪問到的節點

