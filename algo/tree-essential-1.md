樹問題小結：大纲、树的创建/拷贝/销毁
====

樹的基礎知識我懶得寫了，請直接參考[馬叔叔](http://users.cis.fiu.edu/~weiss/)的書。這裡主要總結關於樹的一些或基本或重要或有趣的問題（不包括高級樹形結構如 [AVL Tree](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/avl-tree.md), [Splay Tree](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/splay-tree.md) 等等），主要包括：

 - **樹的建立**
    * 建隨機樹
    * 建二叉搜索樹
 - **樹的銷燬**
 - **[樹的遍歷](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-traverse.md)**
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
 - **樹的最小深度與最大深度問題**
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
namespace tree {

#define TREE_DEBUG_ENABLED

#ifdef TREE_DEBUG_ENABLED
#  define TREE_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define TREE_DEBUG(fmt, ...)  do {} while (0)
#endif

template<typename T>
struct __tree_node {
    T value;
    __tree_node <T>* left;
    __tree_node <T>* right;
    __tree_node() :
        value(T()), left(NULL), right(NULL) {
    }
    __tree_node(const T& _value) :
        value(_value), left(NULL), right(NULL) {
    }
};

// ranomly picked prime number
static int const MAX_RAND_NUM = 97;
static std::minstd_rand0 __generator((unsigned) time(0));

typedef std::minstd_rand0::result_type default_value_type;

inline default_value_type random_tree_value() {
    return __generator() % MAX_RAND_NUM;
}

} // end of namespace tree
```

## 樹的建立
```C++
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <ctime>
#include <deque>

enum InsertOption {
    ToLeft, ToRight
};

template<typename Argument>
struct insert_optioner: public std::binary_function<Argument, Argument, InsertOption> {
    inline InsertOption operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const;
};

template<typename Argument>
struct random_optioner: insert_optioner<Argument> {
    inline InsertOption operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const {
        return __generator() & 0x1u ? ToLeft : ToRight;
    }
};

template<typename Argument>
struct binary_search_tree_optioner: insert_optioner<Argument> {
    inline InsertOption operator()(const Argument& __curr_arg,
            const Argument& __new_arg) const {
        return __curr_arg > __new_arg ? ToLeft : ToRight;
    }
};

//
// create tree below
// 

template<typename T, typename Optioner>
void __insert_tree(__tree_node <T>* root, __tree_node <T>* node,
        const Optioner& optioner) {
    if (root == NULL || node == NULL) {
        return;
    }
    __tree_node <T>* curr = root;
    while (true) {
        if (optioner(curr->value, node->value) == ToLeft) {
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
}

template<typename InputIterator, typename Optioner = random_optioner<
        typename InputIterator::value_type> >
__tree_node <typename InputIterator::value_type>* create_tree(InputIterator first,
        InputIterator last,
        const Optioner& optioner =
                random_optioner<typename InputIterator::value_type>()) {
    typedef typename InputIterator::value_type value_type;
    __tree_node <value_type>* root = new __tree_node <value_type>(*first);
    while (++first != last) {
        __tree_node <value_type>* node = new __tree_node <value_type>(*first);
        __insert_tree(root, node, optioner);
    }
    return root;
}
```

##樹的銷燬
```C++
// Java估計不存在這個問題了
template<typename T>
void release_tree(__tree_node <T>* tree) {
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
```

## 樹的深拷貝
```C++
// recursively copy a tree
template<typename T>
__tree_node <T>* recursively_copy_tree(__tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }

    __tree_node <T>* newtree = new __tree_node <T>(tree->value);
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
__tree_node <T>* iteratively_copy_tree(__tree_node <T>* tree) {
    if (tree == NULL) {
        return NULL;
    }

    std::deque<__tree_node <T>*> queue1;
    queue1.push_back(tree);
    std::deque<__tree_node <T>*> queue2;
    __tree_node <T>* newtree = new __tree_node <T>(tree->value);
    queue2.push_back(newtree);

    __tree_node <T>* orinode;
    __tree_node <T>* newnode;
    while (!queue1.empty()) {
        orinode = queue1.front();
        queue1.pop_front();
        newnode = queue2.front();
        queue2.pop_front();

        if (orinode->left) {
            queue1.push_back(orinode->left);
            newnode->left = new __tree_node <T>(orinode->left->value);
            queue2.push_back(newnode->left);
        }
        if (orinode->right) {
            queue1.push_back(orinode->right);
            newnode->right = new __tree_node <T>(orinode->right->value);
            queue2.push_back(newnode->right);
        }
    }

    return newtree;
}
```

##樹的遍歷

完整的討論在[這裡](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-traverse.md)，包括遞歸與非遞歸方式的遍歷，下面主要是為了文章結尾的測試...

```C++
template<typename Argument>
struct tree_node_accessor: public std::unary_function<Argument, void> {
    inline void operator()(const Argument& __arg) const;
};

template<typename Argument>
struct tree_node_printer: tree_node_accessor<Argument> {
    inline void operator()(const Argument& __arg) const {
        std::cout << __arg << " ";
    }
};

template<typename Type, typename Accessor = tree_node_printer<Type> >
void pre_order(__tree_node <Type>* root, const Accessor& accessor =
        tree_node_printer<Type>()) {
    if (root != NULL) {
        accessor(root->value);
        pre_order(root->left);
        pre_order(root->right);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void in_order(__tree_node <Type>* root, const Accessor& accessor =
        tree_node_printer<Type>()) {
    if (root) {
        in_order(root->left);
        accessor(root->value);
        in_order(root->right);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void post_order(__tree_node <Type>* root,
        const Accessor& accessor = tree_node_printer<Type>()) {
    if (root) {
        post_order(root->left);
        post_order(root->right);
        accessor(root->value);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void level_order(__tree_node <Type>* root,
        const Accessor& accessor = tree_node_printer<Type>()) {
    std::deque<__tree_node <Type>*> queue;
    queue.push_back(root);
    queue.push_back(NULL);
    __tree_node <Type>* curr;
    while (!queue.empty()) {
        curr = queue.front();
        queue.pop_front();

        if (curr) {
            accessor(curr->value);
            if (curr->left) {
                queue.push_back(curr->left);
            }
            if (curr->right) {
                queue.push_back(curr->right);
            }
        } else {
            if (!queue.empty()) {
                std::cout << "# ";
                queue.push_back(NULL);
            }
        }
    }
}
```
## 建立/銷燬/深拷貝的測試

完整的代碼在[這裡](https://github.com/g7tianyi/my-acm-solutions/blob/master/repo/tree.cc)。

```C++
typedef tree::default_value_type value_type;

enum CreateTreeMode {
    RANDOM, BST
};

enum CopyTreeMode {
    RECURSION, ITERATION
};

tree::__tree_node<value_type>* __test_create_tree(std::vector<value_type>& vec,
        CreateTreeMode mode) {
    if (mode == RANDOM) {
        return tree::create_tree(vec.begin(), vec.end());
    } else {
        tree::binary_search_tree_optioner<value_type> bst_picker;
        return tree::create_tree(vec.begin(), vec.end(), bst_picker);
    }
}

void test_create_random_tree(std::vector<value_type>& vec) {
    std::cout << "test create random tree\n";
    tree::__tree_node<value_type>* root = __test_create_tree(vec, RANDOM);
    tree::in_order(root), std::cout << "\n";
    tree::pre_order(root), std::cout << "\n";
    tree::post_order(root), std::cout << "\n";
    tree::level_order(root), std::cout << "\n";
    tree::release_tree(root), std::cout << "\n";
}

void test_create_binary_search_tree(std::vector<value_type>& vec) {
    std::cout << "test create binary search tree\n";
    tree::__tree_node<value_type>* root = __test_create_tree(vec, BST);
    tree::in_order(root), std::cout << "\n";
    tree::pre_order(root), std::cout << "\n";
    tree::post_order(root), std::cout << "\n";
    tree::level_order(root), std::cout << "\n";
    tree::release_tree(root), std::cout << "\n";
}

void __test_copy_tree(std::vector<value_type>& vec, CopyTreeMode mode) {
    tree::__tree_node<value_type>* root = __test_create_tree(vec, BST);
    tree::in_order(root), std::cout << "\n";
    tree::pre_order(root), std::cout << "\n";
    tree::post_order(root), std::cout << "\n";
    tree::level_order(root), std::cout << "\n";

    tree::__tree_node<value_type>* newroot = NULL;
    if (mode == RECURSION) {
        newroot = tree::recursively_copy_tree(root);
    } else {
        newroot = tree::iteratively_copy_tree(root);
    }
    tree::in_order(newroot), std::cout << "\n";
    tree::pre_order(newroot), std::cout << "\n";
    tree::post_order(newroot), std::cout << "\n";
    tree::level_order(newroot), std::cout << "\n";

    tree::release_tree(root);
    tree::release_tree(newroot);
    std::cout << "\n";
}

void test_recursively_copy_tree(std::vector<value_type>& vec) {
    std::cout << "test recursively copy tree\n";
    __test_copy_tree(vec, RECURSION);
}

void test_iteratively_copy_tree(std::vector<value_type>& vec) {
    std::cout << "test iteratively copy tree\n";
    __test_copy_tree(vec, ITERATION);
}


int main() {

    const int TEST_DATA_SIZE = 17;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value());
    }

    test_create_random_tree(vec);
    test_create_binary_search_tree(vec);

    test_recursively_copy_tree(vec);
    test_iteratively_copy_tree(vec);

    return 0;
}
```

*未完待續...*


