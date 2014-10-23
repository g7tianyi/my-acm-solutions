#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    typedef TreeNode* nodeptr;
    void recoverTree(nodeptr root) {
        if (root == NULL) {
            return;
        }
        prev = error1 = error2 = NULL;
        inOrderTraverse(root);
        std::swap(error1->val, error2->val);
    }
private:
    nodeptr prev, error1, error2;
    void inOrderTraverse(nodeptr root) {
        if (root == NULL) {
            return;
        }
        inOrderTraverse(root->left);
        if (prev && prev->val > root->val) {
            if (error1 == NULL) {
                error1 = prev, error2 = root;
            } else {
                error2 = root;
            }
        }
        prev = root;
        inOrderTraverse(root->right);
    }
};

