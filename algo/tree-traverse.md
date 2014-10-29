樹的遍歷總結
=========
``` C++
// Firstly, definition of (Binary) TreeNode
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() :
        val(0), left(NULL), right(NULL) {
    }
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};
```
前序遍歷
----
```C++
// recursive style
void preOrderRecursion(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preOrderRecursion(root->left);
        preOrderRecursion(root->right);
    }
}
// iterative style
void preOrderIteration(TreeNode* root) {
    std::stack<TreeNode*> stack;
    TreeNode* curr = root;
    while (curr || !stack.empty()) {
        while (curr) {
            printf("%d ", curr->val);
            stack.push(curr);
            curr = curr->left;
        }
        if (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            curr = curr->right;
        }
    }
}
```
中序遍歷
----
```C++
// recursive style
void inOrderRecursion(TreeNode* root) {
    if (root) {
        inOrderRecursion(root->left);
        printf("%d ", root->val);
        inOrderRecursion(root->right);
    }
}
// iterative style
void inOrderIteration(TreeNode* root) {
    std::stack<TreeNode*> stack;
    TreeNode* curr = root;
    while (curr || !stack.empty()) {
        while (curr) {
            stack.push(curr);
            curr = curr->left;
        }
        if (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            printf("%d ", curr->val);
            curr = curr->right;
        }
    }
}
```
後序遍歷
----
```C++
// recursive style
void postOrderRecursion(TreeNode* root) {
    if (root) {
        postOrderRecursion(root->left);
        postOrderRecursion(root->right);
        printf("%d ", root->val);
    }
}

/**
 * Idea:
 * for any node curr, push it into the stack. if curr is a leaf node, access it
 * directly, or if both of its left and right child node has been accessed,
 * access it directly. otherwise, push its right child and left child into the
 * stack.
 *
 * e.g., for the following tree,
 *          0
 *        /   \
 *       1     2
 *     /  \   /  \
 *    3   4  5    6
 *   / \  /  \   / \
 *  7  8 9   10 11  12
 *
 * the stack status are:
 *     #
 *     0
 *     0 2 1
 *     0 2 1 4 3
 *     0 2 1 4 3 8 7
 *     0 2 1 4 3 8
 *     0 2 1 4 3
 *     0 2 1 4 9
 *     0 2 1 4
 *     0 2 1
 *     0 2
 *     0 2 6 5
 *     0 2 6 5 10
 *     0 2 6 5
 *     0 2 6
 *     0 2 6 12 11
 *     0 2 6 12
 *     0 2 6
 *     0 2
 *     0
 *     #
 */
void postOrderIteration(TreeNode* root) {
    std::stack<TreeNode*> stack;
    TreeNode *curr, *prev = NULL;
    stack.push(root);
    while (!stack.empty()) {
        curr = stack.top();
        if ((curr->left == NULL && curr->right == NULL) // leaf node
                || (prev != NULL
                        && (prev == curr->left || prev == curr->right))) {
            printf("%d ", curr->val);
            stack.pop();
            prev = curr;
        } else {
            if (curr->right != NULL) {
                stack.push(curr->right);
            }
            if (curr->left != NULL) {
                stack.push(curr->left);
            }
        }
    }
}
```
層序遍歷
---
```C++
#include <deque>

void levelOrder(TreeNode* root) {
    std::deque<TreeNode*> queue;
    queue.push_back(root);
    queue.push_back(NULL);
    TreeNode* curr;
    while (!queue.empty()) {
        curr = queue.front();
        queue.pop_front();

        if (curr) {
            printf("%d ", curr->val);
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
#include <cstdio>
#include <stack>

static int const NODE_COUNT = 13;
TreeNode nodes[NODE_COUNT];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i;
    }
    //////////////////////////
    //          0           //
    //        /   \         //
    //       1     2        //
    //     /  \   /  \      //
    //    3    4 5    6     //
    //   / \  /  \   / \    //
    //  7  8 9   10 11  12  //
    //////////////////////////
    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9], nodes[5].right = &nodes[10];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];

    TreeNode* root = &nodes[0];

    printf("Test in order traverse: \n");
    inOrderRecursion(root), printf("\n");
    inOrderIteration(root), printf("\n");

    printf("Test pre order traverse: \n");
    preOrderRecursion(root), printf("\n");
    preOrderIteration(root), printf("\n");

    printf("Test post order traverse: \n");
    postOrderRecursion(root), printf("\n");
    postOrderIteration(root), printf("\n");

    printf("Test level order traverse: \n");
    levelOrder(root), printf("\n");
    
    return 0;
}
```

