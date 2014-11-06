樹問題小結：樹的K最值問題
====
問題來自[馬叔叔](http://users.cis.fiu.edu/~weiss/)的 *Data Structures And Algorithm Analysis*，感謝馬叔叔呀~

> Suppose we want to add the operation **findKth**  to our repertoire. The operation **findKth(k)** returns the kth smallest item in the tree. Assume all items are distinct. Explain how to modify the binary search tree to support this operation in O(logN) average time, without sacrificing the time bounds of any other operation.

## 直覺想法

[中序遍歷](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-traverse.md)，然後就能直接選出第K大或是第K小的元素。不過這個是O(N)算法，算是warming up.

## 數據結構的改进

馬叔叔說了，"Explain how to modify the binary search tree"，那就架起CLRS第14章，更新數據結構吧。

為了實現求第K小的二叉搜索樹，最直接的想法是能否在每個樹節點上維護自身的位置。但這個辦法有麻煩，因為插入或刪除一個節點時，最差情況是每個節點的位置信息都要被更新（插入或刪除一個最小值的情況），時間複雜度O(N)，其實管你最好還是最壞，平攤的複雜度就是O(N)，無法滿足馬叔叔說的 "without sacrificing the time bounds of any other operation"。

考慮到二叉搜索樹的左子樹都比自己小，右子樹都比自己大，因此左子樹節點數+1就是以自己的位置信息，事實上這個貌似就是Size Balanced Tree的思想，不過這個樹我就聽說過沒仔細學習過，改天仔細學習一下。

现在，当插入节点时：

- 如果往左子树走，当年节点的位置信息加1

- 如果往右子树走，节点位置信息不变

就这么回事儿！

```C++
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <ctime>
#include <deque>
#include <stack>

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
struct __tree_node {
    T value;
    __tree_node <T>* left;
    __tree_node <T>* right;
    __tree_node() :
        value(T()),left(NULL), right(NULL) {
    }
    __tree_node(const T& _value) :
        value(_value), left(NULL), right(NULL) {
    }
};

template<typename T>
struct __kth_tree_node: public __tree_node<T> {
    unsigned left_size; // size of the left subtree
    __kth_tree_node() :
        __tree_node<T>(), left_size(0) {
    }
    __kth_tree_node(const T& _value) :
        __tree_node<T>(_value), left_size(0) {
    }
};

template<typename Type>
void pre_order(__kth_tree_node <Type>* root) {
    if (root != NULL) {
        std::cout << root->value << "(" << root->left_size << ") ";
        pre_order((__kth_tree_node <Type>*) root->left);
        pre_order((__kth_tree_node <Type>*) root->right);
    }
}

template<typename Type>
void in_order(__kth_tree_node <Type>* root) {
    if (root) {
        in_order((__kth_tree_node <Type>*) root->left);
        std::cout << root->value << "(" << root->left_size << ") ";
        in_order((__kth_tree_node <Type>*) root->right);
    }
}

template<typename Type>
void post_order(__kth_tree_node <Type>* root) {
    if (root) {
        post_order((__kth_tree_node <Type>*) root->left);
        post_order((__kth_tree_node <Type>*) root->right);
        std::cout << root->value << "(" << root->left_size << ") ";
    }
}

template<typename Type>
void level_order(__kth_tree_node <Type>* root) {
    std::deque<__kth_tree_node <Type>*> queue;
    queue.push_back(root);
    queue.push_back(NULL);
    __kth_tree_node <Type>* curr;
    while (!queue.empty()) {
        curr = queue.front();
        queue.pop_front();

        if (curr) {
            std::cout << curr->value << "(" << curr->left_size << ") ";
            if (curr->left) {
                queue.push_back((__kth_tree_node <Type>*) curr->left);
            }
            if (curr->right) {
                queue.push_back((__kth_tree_node <Type>*) curr->right);
            }
        } else {
            if (!queue.empty()) {
                std::cout << "# ";
                queue.push_back(NULL);
            }
        }
    }
}

//
// create tree below
//
template<typename T>
bool __insert_k_elem_search_tree(__kth_tree_node <T>* root, __kth_tree_node <T>* node) {
    if (root == NULL || node == NULL) {
        return true;
    }
    __kth_tree_node <T>* curr = root;
    while (true) {
        if (node->value == curr->value) {
            LOG_DEBUG("duplicate value : %d, skip it.", node->value);
            return false;
        }
        if (node->value < curr->value) {
            ++curr->left_size;
            if (curr->left) {
                curr = (__kth_tree_node <T>*) curr->left;
            } else {
                curr->left = node;
                break;
            }
        } else {
            if (curr->right) {
                curr = (__kth_tree_node <T>*) curr->right;
            } else {
                curr->right = node;
                break;
            }
        }
    }
    return true;
}

template<typename InputIterator>
__kth_tree_node <typename InputIterator::value_type>* create_tree(InputIterator first,
        InputIterator last) {
    typedef typename InputIterator::value_type value_type;
    __kth_tree_node <value_type>* root = new __kth_tree_node <value_type>(*first);
    while (++first != last) {
        __kth_tree_node <value_type>* node = new __kth_tree_node <value_type>(*first);
        if (!__insert_k_elem_search_tree(root, node)) {
            delete node;
        }
    }
    return root;
}

// the recursion is rear recusion, which on one hand, is quite efficient, and on the other
// hand, makes it very easy to rewrite in iterative style
template<typename T>
__kth_tree_node <T>* find_kth_elem(__kth_tree_node <T>* tree, unsigned k) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->left_size + 1 == k) {
        return tree;
    }
    if (tree->left_size + 1 > k) {
        return find_kth_elem((__kth_tree_node <T>*) tree->left, k);
    }
    return find_kth_elem((__kth_tree_node <T>*) tree->right, k - (tree->left_size + 1));
}

//template<typename T>
//void remove_elem(__kth_tree_node <T>* tree, unsigned k) {
//    if (tree == NULL) {
//        return;
//    }
//    if (tree->left_size + 1 == k) {
//       find the predecessor of curr node, append it here
//    }
//    if (tree->left_size + 1 > k) {
//        --tree->left_size;
//        recursively search the left sub tree
//    }
//    search the right sub tree
//}


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

} // end of namespace tree

//
// test below
//
typedef tree::default_value_type value_type;

int main() {

    const int TEST_DATA_SIZE = 17;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value() + 1);
    }
    tree::__kth_tree_node<value_type>* tree = tree::create_tree(vec.begin(), vec.end());

    std::cout << "in order   : "; in_order(tree); std::cout << "\n";
    std::cout << "pre order  : "; pre_order(tree); std::cout << "\n";
    std::cout << "post order : "; post_order(tree); std::cout << "\n";
    std::cout << "level order: "; level_order(tree); std::cout << "\n";

    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        tree::__kth_tree_node<value_type>* node = find_kth_elem(tree, i + 1);
        std::cout << "searching " << i + 1 << " items: " << (node ? node->value : -1)
                << std::endl;
    }

    tree::release_tree(tree);

    return 0;
}
```
