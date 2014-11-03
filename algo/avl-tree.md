AVL樹
====
> 致謝： http://zh.wikipedia.org/wiki/AVL%E6%A0%91

AVL樹作為歷史上第一個被發明出來的平衡樹，優雅的旋轉和優越的性能讓其成為所有教材講到平衡樹時的第一選擇，我也是因為那些優雅的旋轉從對數據結構問題既漸漸有了“things are under control”的感覺，又有了很濃厚的興趣~

我是通過Mark Allen Weiss的寶書《數據結構與算法分析》理解AVL樹的，下面的代碼也參考Mark叔叔的書，不過下面借用一下Wikipedia的圖片。

![AVL樹的平衡示意圖](http://upload.wikimedia.org/wikipedia/commons/c/c7/Tree_Rebalancing.png)

編程實現
----
```C++
/**
 * 主要注意以下幾個函數的實現，旋轉的關鍵盡在於此了
 *
 * AVLTreeNode<T>* ll_rotate(AVLTreeNode<T>* k2);
 * AVLTreeNode<T>* rr_rotate(AVLTreeNode<T>* k1);
 * AVLTreeNode<T>* lr_rotate(AVLTreeNode<T>* k3);
 * AVLTreeNode<T>* rl_rotate(AVLTreeNode<T>* k3);
 * AVLTreeNode<T>* rebalance(AVLTreeNode<T>* k0);
 */

#include <iostream>

namespace avltree {

template<typename T>
struct AVLTreeNode {
public:
    T key;
    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;
    int height;

    AVLTreeNode() :
        key(T()), left(NULL), right(NULL), height(0) {
    }
    AVLTreeNode(T key_) :
        key(key_), left(NULL), right(NULL), height(0) {
    }
};

template<class T> class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    int height();
    T minimum();
    T maximum();

    T predecessor(const T& key);
    T successor(const T& key);

    AVLTreeNode<T>* get_root() const;
    AVLTreeNode<T>* find(const T& key) const;
    void insert(T key);
    void remove(const T& key);

private:
    int height(AVLTreeNode<T>* tree);

    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

    AVLTreeNode<T>* predecessor(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* successor(AVLTreeNode<T>* tree);

    AVLTreeNode<T>* find(AVLTreeNode<T>* x, const T& key) const;
    AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, const T& key);
    AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* k0);

    void release(AVLTreeNode<T>* tree);

private:
    AVLTreeNode<T>* ll_rotate(AVLTreeNode<T>* k2);
    AVLTreeNode<T>* rr_rotate(AVLTreeNode<T>* k1);
    AVLTreeNode<T>* lr_rotate(AVLTreeNode<T>* k3);
    AVLTreeNode<T>* rl_rotate(AVLTreeNode<T>* k3);
    AVLTreeNode<T>* rebalance(AVLTreeNode<T>* k0);

private:
    AVLTreeNode<T>* root;
};


//////////////////////////////////////////////////////////////////////////
// implementations
//

template<typename T>
inline AVLTree<T>::AVLTree() : root(NULL) {
}

template<typename T>
inline AVLTree<T>::~AVLTree() {
    release(root);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::get_root() const {
    return root;
}

template<typename T>
inline int AVLTree<T>::height(AVLTreeNode<T>* tree) {
    if (tree) {
        return tree->height;
    }
    return 0;
}

template<typename T>
inline int AVLTree<T>::height() {
    return height(root);
}

/**
 * return the node with key equals to the input key,
 * if no such node exists, return the node
 */
template<typename T>
AVLTreeNode<T>* AVLTree<T>::find(AVLTreeNode<T>* node, const T& key) const {
    AVLTreeNode<T>* curr = node;
    AVLTreeNode<T>* prev = NULL;
    while (curr) {
        if (key == curr->key) {
            return curr;
        }
        prev = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return prev;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::find(const T& key) const {
    return find(root, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree) {
    if (tree == NULL) {
        return NULL;
    }
    while (tree->left) {
        tree = tree->left;
    }
    return tree;
}

template<typename T>
T AVLTree<T>::minimum() {
    AVLTreeNode<T>* node = minimum(root);
    if (node) {
        return node->key;
    }
    return T();
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree) {
    if (tree == NULL) {
        return NULL;
    }
    while (tree->right) {
        tree = tree->right;
    }
    return tree;
}

template<typename T>
T AVLTree<T>::maximum() {
    AVLTreeNode<T>* node = maximum(root);
    if (node) {
        return node->key;
    }
    return T();
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::predecessor(AVLTreeNode<T>* tree) {
    if (tree) {
        return maximum(tree->left);
    }
    return NULL;
}

template<typename T>
T AVLTree<T>::predecessor(const T& key) {
    AVLTreeNode<T>* node = find(key);
    if (node == NULL) {
        return T(); // may be not a good idea
    }
    if (node->key == key) {
        return key;
    }
    node = maximum(node->right);
    return node ? node->key : T();
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::successor(AVLTreeNode<T>* tree) {
    if (tree) {
        return minimum(tree->right);
    }
    return NULL;
}

template<typename T>
T AVLTree<T>::successor(const T& key) {
    AVLTreeNode<T>* node = find(key);
    if (node == NULL) {
        return T(); // may be not a good idea
    }
    if (node->key == key) {
        return key;
    }
    node = minimum(node->right);
    return node ? node->key : T();
}

//
// for the following 4 IMPORTANT functions in regards to rotations
// please refer to "Data Structures and Algorithm Analysis" by Mark Allen Weiss
// k1, k2, k3 comes from the illustration of this book
//

/**
 * LL rotate:
 *
 *             8 (k2)            4
 *           /   \             /   \
 *     (k1) 4     9    =>     2     8
 *        /   \             /      /  \
 *       2     6           1      6    9
 *     /
 *    1
 */
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::ll_rotate(AVLTreeNode<T>* k2) {
    AVLTreeNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), k2->height) + 1;

    return k1;
}

/**
 * RR rotate:
 *
 *       3 (k1)                    5
 *     /   \                     /   \
 *    2     5 (k2)      =>      3     8
 *        /   \               /  \   /  \
 *       4     8             2    4 7    9
 *           /   \
 *          7     9
 */
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::rr_rotate(AVLTreeNode<T>* k1) { // k1 is 3 in the figure
    AVLTreeNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2->height = std::max(height(k2->left), k1->height) + 1;

    return k2;
}

/**
 * LR rotate:
 *
 *         8 (k3)               8 (k3)               6 (k2)
 *       /   \      RR        /   \      LL        /   \
 * (k1) 4     9     =>  (k2) 6     9     =>  (k1) 4     8 (k3)
 *    /   \                /   \                /  \   /  \
 *   2     6 (k2)    (k1) 4     7              2    5 7    9
 *       /  \           /  \
 *      5    7         2    5
 */
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::lr_rotate(AVLTreeNode<T>* k3) {
    if (k3) {
        k3->left = rr_rotate(k3->left);
        return ll_rotate(k3);
    }
    return NULL;
}

/**
 * RL rotate:
 *
 *      3 (k3)              3 (k3)                 6
 *    /   \               /   \                  /   \
 *   2     8 (k1)   =>   2     6 (k2)    =>     3     8
 *        /  \               /  \             /  \   /  \
 *  (k2) 6    9             5    8 (k1)      2    5 7    9
 *     /  \                    /  \
 *    5    7                  7    9
 */
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::rl_rotate(AVLTreeNode<T>* k3) {
    if (k3) {
        k3->right = rr_rotate(k3->right);
        return rr_rotate(k3);
    }
    return NULL;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::rebalance(AVLTreeNode<T>* k0) {
    if (k0 == NULL) {
        return k0;
    }

    if (height(k0->left) - height(k0->right) > 1) {
        if (height(k0->left->left) >= height(k0->left->right)) {
            k0 = ll_rotate(k0);
        } else {
            k0 = lr_rotate(k0);
        }
    } else if (height(k0->right) - height(k0->left) > 1) {
        if (height(k0->right->right) >= height(k0->right->left)) {
            k0 = rr_rotate(k0);
        } else {
            k0 = rl_rotate(k0);
        }
    }

    k0->height = std::max(height(k0->left), height(k0->right)) + 1;
    return k0;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, const T& key) {
    if (tree == NULL) {
        tree = new AVLTreeNode<T>(key);
        return tree;
    } else if (key < tree->key) {
        tree->left = insert(tree->left, key);
    } else if (key > tree->key) {
        tree->right = insert(tree->right, key);
    } else { // duplicates, skip
        ;
    }
    return rebalance(tree);
}

template<typename T>
void AVLTree<T>::insert(T key) {
    insert(root, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* k0) {
    if(tree == NULL || k0 == NULL) {
        return NULL;
    }

    if (k0->key == tree->key) {
        if (tree->left && tree->right) {
            if (height(tree->left) > height(tree->right)) {
                AVLTreeNode<T>* pred = predecessor(tree);
                tree->key = pred->key;
                tree->left = remove(tree->left, pred);
            } else {
                AVLTreeNode<T>* succ = predecessor(tree);
                tree->key = succ->key;
                tree->right = remove(tree->right, succ);
            }
        } else {
            AVLTreeNode<T>* temp = tree;
            tree = tree->left ? tree->left : tree->right;
            delete temp;
        }
        return tree;
    }

    if (k0->key < tree->key) {
        tree->left = remove(tree->left, k0);
    } else if (k0->key > tree->key) {
        tree->right = remove(tree->right, k0);
    }
    return rebalance(tree);
}

template<typename T>
void AVLTree<T>::remove(const T& key) {
    AVLTreeNode<T>* node = find(root, key);
    if (node) {
        remove(root, node);
    }
}

template<typename T>
void AVLTree<T>::release(AVLTreeNode<T>* tree) {
    if (tree == NULL) {
        return;
    }
    release(tree->left);
    release(tree->right);
    delete tree;
}

}
```
測試輔助代碼
----
```C++
//////////////////////////////////////////////////////////////////////////
// helper
//
#include <deque>

template<typename T>
void preOrder(avltree::AVLTreeNode<T>* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

template<typename T>
void inOrder(avltree::AVLTreeNode<T>* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

template<typename T>
void postOrder(avltree::AVLTreeNode<T>* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

template<typename T>
void levelOrder(avltree::AVLTreeNode<T>* root) {
    std::deque<avltree::AVLTreeNode<T>*> queue;
    queue.push_back(root);
    queue.push_back(NULL);
    avltree::AVLTreeNode<T>* curr;
    while (!queue.empty()) {
        curr = queue.front();
        queue.pop_front();

        if (curr) {
            printf("%d ", curr->key);
            if (curr->left) {
                queue.push_back(curr->left);
            }
            if (curr->right) {
                queue.push_back(curr->right);
            }
        } else {
            if (!queue.empty()) {
                printf("# ");
                queue.push_back(NULL);
            }
        }
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
    TEST_SIZE = 12, MAX_NUM = 100,
};

int main() {
    srand((unsigned) time(0));
    std::random_device rd;
    std::mt19937 g(rd());

    avltree::AVLTree<int> avltree;

    // 1) insert
    std::vector<int> vec;
    for (int i = 0, num; i < TEST_SIZE; ++i) {
        num = (rand() % MAX_NUM) + 1;
        vec.push_back(num);
        avltree.insert(num);
    }

    // 2) in/pre/post/level order
    avltree::AVLTreeNode<int>* root = avltree.get_root();
    printf("in order: "), inOrder(root), printf("\n");
    printf("pre order: "), preOrder(root), printf("\n");
    printf("post order: "), postOrder(root), printf("\n");
    printf("level order: "), levelOrder(root), printf("\n");

    // 3) find
    std::shuffle(vec.begin(), vec.end(), g);
    for (int i = 0; i < TEST_SIZE; ++i) {
        avltree::AVLTreeNode<int>* node = avltree.find(vec[i]);
        printf("find %d: ", vec[i]);
        if (node) {
            printf("succeed\n");
        } else {
            printf("failed\n");
        }
    }
    printf("------------------------\n");

    // 4) predecessor, successor
    for (int i = 0; i < TEST_SIZE; ++i) {
        printf("predecessor of %d: %d\n", vec[i], avltree.predecessor(vec[i]));
        printf("predecessor of %d: %d\n", vec[i] - 1, avltree.predecessor(vec[i] - 1));
        printf("predecessor of %d: %d\n", vec[i] + 1, avltree.predecessor(vec[i] + 1));

        printf("successor of %d: %d\n", vec[i], avltree.successor(vec[i]));
        printf("successor of %d: %d\n", vec[i] - 1, avltree.successor(vec[i] - 1));
        printf("successor of %d: %d\n", vec[i] + 1, avltree.successor(vec[i] + 1));
    }
    printf("------------------------\n");

    // 5) remove
    std::shuffle(vec.begin(), vec.end(), g);
    for (int i = 0; i < TEST_SIZE; ++i) {
        avltree.remove(vec[i]);
        printf("remove %d\n", vec[i]);
    }
    printf("------------------------\n");

    return 0;
}
```

