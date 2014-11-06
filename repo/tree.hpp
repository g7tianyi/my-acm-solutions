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
// tree traverse below
//
// tree traverse below
// please refer to https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-traverse.md
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
void pre_order(tree_node <Type>* root, const Accessor& accessor =
        tree_node_printer<Type>()) {
    if (root != NULL) {
        accessor(root->value);
        pre_order(root->left);
        pre_order(root->right);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void in_order(tree_node <Type>* root, const Accessor& accessor =
        tree_node_printer<Type>()) {
    if (root) {
        in_order(root->left);
        accessor(root->value);
        in_order(root->right);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void post_order(tree_node <Type>* root,
        const Accessor& accessor = tree_node_printer<Type>()) {
    if (root) {
        post_order(root->left);
        post_order(root->right);
        accessor(root->value);
    }
}

template<typename Type, typename Accessor = tree_node_printer<Type> >
void level_order(tree_node <Type>* root,
        const Accessor& accessor = tree_node_printer<Type>()) {
    std::deque<tree_node <Type>*> queue;
    queue.push_back(root);
    queue.push_back(NULL);
    tree_node <Type>* curr;
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

// find element in binary search tree, iterative style
template<typename T>
tree_node <T>* find_elem_in_bst(tree_node <T>* tree, const T& value) {
    tree_node <T>* curr = tree;
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
tree_node <T>* find_elem_in_bst_recursion(tree_node <T>* tree, const T& value) {
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
tree_node <T>* find_elem_in_brt(tree_node <T>* tree, const T& value) {
    if (tree == NULL) {
        return NULL;
    }
    // it is just a tree traversing problem in iterative style
    // below is a pre-order traversing
    std::stack<tree_node <T>*> stack;
    tree_node <T>* curr = tree;
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

// find element in binary search tree, iterative style
template<typename T>
tree_node <T>* find_elem_in_brt_recursion(tree_node <T>* tree, const T& value) {
    if (tree == NULL || value == tree->value) {
        return tree;
    }
    tree_node <T>* result = find_elem_in_brt_recursion(tree->left, value);
    if (result) {
        return result;
    }
    return find_elem_in_brt_recursion(tree->right, value);
}

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

template<typename T>
bool validate_bst(tree_node <T>* tree, const T& min_elem, const T& max_elem) {
    if (tree == NULL) {
        return true;
    }

    if (tree->value < min_elem || tree->value > max_elem) {
        return false;
    }

    return validate_bst(tree->left, min_elem, tree->value)
            && validate_bst(tree->right, tree->value, max_elem);
}

// in order traverse, the in order sequence should be ordered
template<typename T>
bool validate_bst(tree_node <T>* tree) {
    std::deque<tree_node <T>*> queue;
    std::stack<tree_node <T>*> stack;
    tree_node <T>* curr = tree;
    while (curr || !stack.empty()) {
        while (curr) {
            stack.push(curr);
            curr = curr->left;
        }
        if (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            queue.push_back(curr);
            curr = curr->right;
        }
    }

    if (!queue.empty()) {
        tree_node <T>* prev = queue.front();
        queue.pop_front();
        while (!queue.empty()) {
            curr = queue.front();
            if (curr->value < prev->value) {
                return false;
            }
            prev = curr;
            queue.pop_front();
        }
    }

    return true;
}

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
tree_node <T>* predecessor_in_bst(tree_node <T>* tree, const T& value) {
    tree_node <T>* curr = tree; // curr and parent pointer
    std::deque<tree_node <T>*> ancestors;
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
        tree_node <T>* parent = ancestors.back();
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
tree_node <T>* successor_in_bst(tree_node <T>* tree, const T& value) {
    tree_node <T>* curr = tree; // curr and parent pointer
    std::deque<tree_node <T>*> ancestors;
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
        tree_node <T>* parent = ancestors.back();
        ancestors.pop_back();
        while (parent && parent->left != curr) {
            curr = parent;
            parent = ancestors.back();
            ancestors.pop_back();
        }
        return parent;
    }
}

template<typename T>
tree_node <T>* max_elem(tree_node <T>* tree) {
    while (tree && tree->right) {
        tree = tree->right;
    }
    return tree;
}

template<typename T>
tree_node <T>* min_elem(tree_node <T>* tree) {
    while (tree && tree->left) {
        tree = tree->left;
    }
    return tree;
}

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

// create mirror. iterative style.
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

template<typename T>
bool is_mirror_iterative(tree_node<T>* tree1, tree_node<T>* tree2) {
    std::deque<tree_node<T>*> queue1, queue2;
    queue1.push_back(tree1);
    queue2.push_back(tree2);
    tree_node<T> *curr1, *curr2;

    while (!queue1.empty()) {
        curr1 = queue1.front();
        queue1.pop_front();
        curr2 = queue2.front();
        queue2.pop_front();

        if (curr1 == NULL && curr2 == NULL) {
            continue;
        }

        if (curr1 == NULL && curr2 != NULL) {
            return false;
        }
        if (curr1 != NULL && curr2 == NULL) {
            return false;
        }
        if (curr1->value != curr2->value) {
            return false;
        }

        queue1.push_back(curr1->left);
        queue2.push_back(curr2->right);

        queue1.push_back(curr1->right);
        queue2.push_back(curr2->left);
    }

    return true;
}



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

