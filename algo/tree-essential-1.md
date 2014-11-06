樹問題小結：大綱，樹的創建/拷貝/銷燬
====

樹的基礎知識我懶得寫了，請直接參考[馬叔叔](http://users.cis.fiu.edu/~weiss/)的書。這裡主要總結關於樹的一些或基本或重要或有趣的問題（不包括高級樹形結構如 [AVL Tree](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/avl-tree.md), [Splay Tree](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/splay-tree.md) 等等），主要包括：

 - **樹的建立**
    * 建隨機樹
    * 建二叉搜索樹
 - **樹的銷燬**
 - **[樹的遍歷](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-7.md)**
     * 前序 (遞歸/非遞歸)
     * 中序 (遞歸/非遞歸)
     * 後序 (遞歸/非遞歸)
     * 層序
 - **樹的深拷貝(遞歸/非遞歸)**
 - **樹的比較** 樹的比較其實是比較大的問題，我粗略一想，全面的討論可能至少包括：
     * 判斷兩棵樹是否完全一樣
     * 判斷兩棵樹是否同構（難）
     * 判斷兩棵樹互為鏡像
 - **[樹的節點數問題](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-3.md)**
      * 計算葉子結點的數目
      * 計算非葉子結點的數目
 - **[樹的最小深度與最大深度問題](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-3.md)**
 - **[二叉搜索樹的合法性檢查](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-2.md)**
 - **[二叉搜索樹的前驅、後繼問題](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-2.md)**
 - **[元素的查找](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-4.md)**
 - **[元素的刪除](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-4.md)**
 - **[二叉搜索樹的最值問題](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-2.md), 以及[kMin(), kMax()問題](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-5.md)**
 - **Threaded-Tree的問題（難）**

*還有以後補充...*

這裡主要寫代碼，因為是基礎，基本不知道說什麼。而且老人家沒力氣折騰，只玩二叉樹了~

##（二叉）樹的定義及其他輔助代碼
```C++
#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
#  define LOG_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define LOG_DEBUG(fmt, ...)  do {} while (0)
#endif

namespace tree {

static int const MAX_RAND_NUM = 97;
static std::minstd_rand0 __generator((unsigned) time(0));
typedef std::minstd_rand0::result_type default_value_type;

inline default_value_type random_tree_value() {
    return __generator() % MAX_RAND_NUM;
}

template<typename T>
struct tree_node {
    T value;
    tree_node <T>* left;
    tree_node <T>* right;
    tree_node() :
            value(T()), left(NULL), right(NULL) {
    }
    tree_node(const T& _value) :
            value(_value), left(NULL), right(NULL) {
    }
};

}// end of namespace tree
```

## 樹的建立
```C++

namespace tree {

enum insert_type {
    TO_LEFT, TO_RIGHT, SKIP
};

enum binary_tree_type {
    BINARY_RANDOM_TREE, BINARY_SEARCH_TREE
};

template<typename Argument>
struct insert_optioner: public std::binary_function<Argument, Argument, insert_type> {
    inline insert_type operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const;
};

template<typename Argument>
struct random_optioner: insert_optioner<Argument> {
    inline insert_type operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const {
        return __generator() & 0x1u ? TO_LEFT : TO_RIGHT;
    }
};

template<typename Argument>
struct binary_search_tree_optioner: insert_optioner<Argument> {
    inline insert_type operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const {
        if (__curr_arg == __new_arg) {
            return SKIP;
        }
        return __curr_arg > __new_arg ? TO_LEFT : TO_RIGHT;
    }
};

//
// create tree below
//
template<typename T, typename Optioner>
bool __insert_tree(tree_node <T>* root, tree_node <T>* node,
        const Optioner& optioner) {
    if (root == NULL || node == NULL) {
        return false;
    }
    tree_node <T>* curr = root;
    while (true) {
        if (optioner(curr->value, node->value) == SKIP) {
            return false;
        }
        if (optioner(curr->value, node->value) == TO_LEFT) {
            if (curr->left) {
                curr = curr->left;
            } else {
                curr->left = node;
                break;
            }
        } else {
            if (curr->right) {
                curr = curr->right;
            } else {
                curr->right = node;
                break;
            }
        }
    }
    return true;
}

template<typename InputIterator, typename Optioner = random_optioner<
        typename InputIterator::value_type> >
tree_node <typename InputIterator::value_type>* create_tree(InputIterator first,
        InputIterator last,
        const Optioner& optioner =
                random_optioner<typename InputIterator::value_type>()) {
    typedef typename InputIterator::value_type value_type;
    tree_node <value_type>* root = new tree_node <value_type>(*first);
    while (++first != last) {
        tree_node <value_type>* node = new tree_node <value_type>(*first);
        if (!__insert_tree(root, node, optioner)) {
            delete node;
        }
    }
    return root;
}

} // end of namespace tree
```

##樹的銷燬
```C++

namespace tree {

// release a tree
template<typename T>
void release_tree(tree_node <T>* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->left) {
        release_tree(tree->left);
    }
    if (tree->right) {
        release_tree(tree->right);
    }
    delete tree;
}

} // end of namespace tree
```

## 樹的深拷貝
```C++
// recursively copy a tree
template<typename T>
tree_node <T>* recursively_copy_tree(tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }

    tree_node <T>* newtree = new tree_node <T>(tree->value);
    if (tree->left) {
        newtree->left = recursively_copy_tree(tree->left);
    }
    if (tree->right) {
        newtree->right = recursively_copy_tree(tree->right);
    }
    return newtree;
}

// the essential idea is use a Queue, code itself should be very intuitive
template<typename T>
tree_node <T>* iteratively_copy_tree(tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }

    std::deque<tree_node <T>*> queue1;
    queue1.push_back(tree);
    std::deque<tree_node <T>*> queue2;
    tree_node <T>* newtree = new tree_node <T>(tree->value);
    queue2.push_back(newtree);

    tree_node <T>* orinode;
    tree_node <T>* newnode;
    while (!queue1.empty()) {
        orinode = queue1.front();
        queue1.pop_front();
        newnode = queue2.front();
        queue2.pop_front();

        if (orinode->left) {
            queue1.push_back(orinode->left);
            newnode->left = new tree_node <T>(orinode->left->value);
            queue2.push_back(newnode->left);
        }
        if (orinode->right) {
            queue1.push_back(orinode->right);
            newnode->right = new tree_node <T>(orinode->right->value);
            queue2.push_back(newnode->right);
        }
    }

    return newtree;
}
```
