伸展樹
====
> 致謝： http://www.cppblog.com/MiYu/archive/2010/11/12/133405.html

伸展树(Splay Tree)是AVL树不错的替代，它有以下几个特点：

 1. 它是二叉查找树的改进，所以具有二叉查找树的有序性。
 2. 对伸展树的操作的平摊复杂度是O(log2n)。
 3. 伸展树的空间要求、编程难度非常低。

当我们沿着树向下搜索某个节点X的时候，我们将搜索路径上的节点及其子树移走。我们构建两棵临时的树──左树和右树。没有被移走的节点构成的树称作中树。在伸展操作的过程中：

1. 当前节点X是中树的根
2. 左树L保存小于X的节点
3. 右树R保存大于X的节点

請參考上面博客中的圖。

編程實現
----
```C++
/**
 * Splay tree.
 * Simple implementation.
 */

#include <iostream>

namespace splaytree {

template<typename T> struct TreeNode {
public:
    T key;
    TreeNode* left;
    TreeNode* right;
    TreeNode() :
        key(T()), left(NULL), right(NULL) {
    }
    TreeNode(T _key) :
        key(_key), left(NULL), right(NULL) {
    }
    TreeNode(T _key, TreeNode* _left, TreeNode* _right) :
        key(_key), left(_left), right(_right) {
    }
};

template<typename T> class SplayTree {
public:
    SplayTree();
    ~SplayTree();

    void inOrder();
    void preOrder();
    void postOrder();

    TreeNode<T>* find(T key);

    T minimum();
    T maximum();

    T predecessor(T key);
    T successor(T key);

    void splay(T key);
    void insert(T key);
    void remove(T key);
    void destroy();

    bool empty();

private:
    void inOrder(TreeNode<T>* root) const;
    void preOrder(TreeNode<T>* root) const;
    void postOrder(TreeNode<T>* root) const;

    T minimum(TreeNode<T>* root);
    T maximum(TreeNode<T>* root);

    TreeNode<T>* splay(TreeNode<T>* root, T key);
    TreeNode<T>* insert(TreeNode<T>* root, T key);
    TreeNode<T>* remove(TreeNode<T>* root, T key);

    void destroy(TreeNode<T>* root);

private:
    //      node
    //        |
    // temp   4              2
    //   \  /   \          /   \
    //     2     5   =>   1     4
    //   /   \                /   \
    //  1     3              3     5
    inline TreeNode<T>* __rightRotate(TreeNode<T>* node) {
        TreeNode<T>* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }
    //   node
    //     |
    //     4   temp           6
    //   /   \ /            /   \
    //  3     6       =>   4     7
    //      /   \        /   \
    //     5     7      3     5
    inline TreeNode<T>* __leftRotate(TreeNode<T>* node) {
        TreeNode<T>* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

private:
    TreeNode<T>* treeroot;
};

//////////////////////////////////////////////////////////////////////////
// implementations
//

template<typename T>
SplayTree<T>::SplayTree() :
    treeroot(NULL) {
}

template<typename T>
SplayTree<T>::~SplayTree() {
    destroy(treeroot);
}

template<typename T>
void SplayTree<T>::preOrder(TreeNode<T>* root) const {
    if (root != NULL) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

template<typename T>
void SplayTree<T>::preOrder() {
    preOrder(treeroot);
    std::cout << std::endl;
}

template<typename T>
void SplayTree<T>::inOrder(TreeNode<T>* root) const {
    if (root != NULL) {
        inOrder(root->left);
        std::cout << root->key << " ";
        inOrder(root->right);
    }
}

template<typename T>
void SplayTree<T>::inOrder() {
    inOrder(treeroot);
    std::cout << std::endl;
}

template<typename T>
void SplayTree<T>::postOrder(TreeNode<T>* root) const {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->key << " ";
    }
}

template<typename T>
void SplayTree<T>::postOrder() {
    postOrder(treeroot);
    std::cout << std::endl;
}

template<typename T>
TreeNode<T>* SplayTree<T>::find(T key) {
    TreeNode<T>* curr = treeroot;
    while (curr) {
        if (key == curr->key) {
            return curr;
        }
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}

template<typename T>
T SplayTree<T>::minimum(TreeNode<T>* root) {
    TreeNode<T>* curr = root;
    while (curr->left) {
        curr = curr->left;
    }
    return curr->key;
}

template<typename T>
T SplayTree<T>::minimum() {
    if (treeroot == NULL) {
        return T();
    }
    return minimum(treeroot);
}

template<typename T>
T SplayTree<T>::maximum(TreeNode<T>* root) {
    if (root == NULL) {
        return T();
    }
    TreeNode<T>* curr = root;
    while (curr->right) {
        curr = curr->right;
    }
    return curr->key;
}

template<typename T>
T SplayTree<T>::maximum() {
    if (treeroot == NULL) {
        return T();
    }
    return maximum(treeroot);
}

template<typename T>
T SplayTree<T>::predecessor(T key) {
    TreeNode<T>* root = splay(treeroot, key);
    if (root == NULL) {
        return T();
    } else if (root->key == key && root->left) {
        return maximum(root->left);
    } else {
        return root->key;
    }
}

template<typename T>
T SplayTree<T>::successor(T key) {
    TreeNode<T>* root = splay(treeroot, key);
    if (root == NULL) {
        return T();
    } else if (root->right) {
        return minimum(root->right);
    } else {
        return root->key;
    }
}

template<typename T>
TreeNode<T>* SplayTree<T>::splay(TreeNode<T>* root, T key) {
    if (root == NULL) {
        return NULL;
    }

    TreeNode<T> head;
    TreeNode<T>* leftTree = &head;
    TreeNode<T>* rightTree = &head;

    /**
     * please refer to http://www.cppblog.com/MiYu/archive/2010/11/12/133405.html
     * I'm copy an illustration from this blog for better understanding
     *
     * splaying 19 in the tree
     *
     *   leftTree            Tree               rightTree
     *                        12
     *     empty            /    \                empty
     *                     5     25
     *                          /   \
     *                        20     30
     *                       /   \
     *                     15    24
     *                    /   \
     *                  13    18
     *                       /
     *                     16
     * --------------------------------------------------------------------------
     *   leftTree            Tree              rightTree
     *      12                25
     *     /                /    \
     *    5               20      30             empty
     *                   /  \
     *                 15    24
     *                /  \
     *              13   18
     *                  /
     *                16
     * --------------------------------------------------------------------------
     *    leftTree            Tree              rightTree
     *      12                 15                   20
     *     /                  /  \                    \
     *    5                 13    18                  25
     *                           /                   /  \
     *                          16                 24    30
     * --------------------------------------------------------------------------
     *    leftTree            Tree              rightTree
     *      12                 18                   20
     *     /  \               /                       \
     *    5   15            16                        25
     *       /                                       /   \
     *     13                                      24     30
     * --------------------------------------------------------------------------
     *     leftTree            Tree             rightTree
     *                          18
     *                        /    \
     *                      12      20
     *                     /  \       \
     *                    5   15      25
     *                       /  \    /  \
     *                     13   16  24  30
     * --------------------------------------------------------------------------
     */
    for (;;) {
        if (key < root->key) {
            if (root->left == NULL) {
                break;
            }
            if (key < root->left->key) {
                root = __rightRotate(root);
                if (root->left == NULL) {
                    break;
                }
            }
            rightTree->left = root;
            rightTree = root;
            root = root->left;
        } else if (key > root->key) {
            if (root->right == NULL) {
                break;
            }
            if (key > root->right->key) {
                root = __leftRotate(root);
                if (root->right) {
                    break;
                }
            }
            leftTree->right = root;
            leftTree = root;
            root = root->right;
        } else {
            break;
        }
    }

    leftTree->right = root->left;
    rightTree->left = root->right;
    root->left = head.right;
    root->right = head.left;

    return root;
}

template<typename T>
TreeNode<T>* SplayTree<T>::insert(TreeNode<T>* root, T key) {
    TreeNode<T> *curr = root, *prev = NULL;
    while (curr) {
        prev = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else if (key > curr->key) {
            curr = curr->right;
        } else {
            return curr;
        }
    }

    TreeNode<T>* new_node = new TreeNode<T>(key);
    if (prev == NULL) {
        root = new_node;
    } else if (key < prev->key) {
        prev->left = new_node;
    } else {
        prev->right = new_node;
    }

    return root;
}

template<typename T>
void SplayTree<T>::insert(T key) {
    treeroot = insert(treeroot, key);
    treeroot = splay(treeroot, key);
}

template<typename T>
TreeNode<T>* SplayTree<T>::remove(TreeNode<T>* root, T key) {
    if (root == NULL) {
        return NULL;
    }

    if (find(key) == NULL) {
        return root;
    }

    TreeNode<T>* curr;
    root = splay(root, key);
    if (root->left) {
        // splay the predecessor of root to be the root
        curr = splay(root->left, key);
        curr->right = root->right;
    } else {
        curr = root->right;
    }

    delete root;
    return curr;
}

template<typename T>
void SplayTree<T>::remove(T key) {
    treeroot = remove(treeroot, key);
}

template<typename T>
void SplayTree<T>::destroy(TreeNode<T>* root) {
    if (root == NULL) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

template<typename T>
void SplayTree<T>::destroy() {
    destroy(treeroot);
}

template<typename T>
bool SplayTree<T>::empty() {
    return treeroot == NULL;
}

}
```
測試
----
```C++
//////////////////////////////////////////////////////////////////////////
// test
//

#include <vector>
#include <random>
#include <ctime>

enum {
    TEST_SIZE = 12,
    MAX_NUM = 100,
};

int main() {
    srand((unsigned) time(0));
    std::random_device rd;
    std::mt19937 g(rd());

    splaytree::SplayTree<int> stree;

    // 1) insertion
    std::vector<int> vec;
    for (int i = 0, num; i < TEST_SIZE; ++i) {
        num = (rand() % MAX_NUM) + 1;
        vec.push_back(num);
        stree.insert(num);
    }

    // 2) preOrder, inOrder, postOrder
    stree.inOrder();
    stree.preOrder();
    stree.postOrder();

    // 3) find
    std::shuffle(vec.begin(), vec.end(), g);
    for (int i = 0; i < TEST_SIZE; ++i) {
        splaytree::TreeNode<int>* node = stree.find(vec[i]);
        printf("find %d: ", vec[i]);
        if (node) {
            printf("succeed\n");
        } else {
            printf("failed\n");
        }
    }
    printf("-----------------------\n");

    // 4) predecessor, successor
    for (int i = 0; i < TEST_SIZE; ++i) {
        printf("predecessor of %d: %d\n", vec[i], stree.predecessor(vec[i]));
        printf("predecessor of %d: %d\n", vec[i] - 1, stree.predecessor(vec[i] - 1));
        printf("predecessor of %d: %d\n", vec[i] + 1, stree.predecessor(vec[i] + 1));

        printf("successor of %d: %d\n", vec[i], stree.successor(vec[i]));
        printf("successor of %d: %d\n", vec[i] - 1, stree.successor(vec[i] - 1));
        printf("successor of %d: %d\n", vec[i] + 1, stree.successor(vec[i] + 1));
    }
    printf("-----------------------\n");

    // 5) remove
    std::shuffle(vec.begin(), vec.end(), g);
    for (int i = 0; i < TEST_SIZE; ++i) {
        stree.remove(vec[i]);
        printf("remove %d\n", vec[i]);
    }
    printf("-----------------------\n");

    return 0;
}
```

