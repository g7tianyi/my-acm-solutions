#include <iostream>

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int maxLeft = 0;
        if (root->left) {
            maxLeft = maxDepth(root->left);
        }
        int maxRight = 0;
        if (root->right) {
            maxRight = maxDepth(root->right);
        }
        return 1 + maximum(maxLeft, maxRight);
    }
private:
    inline int maximum(int a, int b) {
        return a > b ? a : b;
    }
};

