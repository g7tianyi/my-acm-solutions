#include <algorithm>

class Solution {
public:
    bool isBalanced(TreeNode *root) {
        return treeHeight(root) != FLAG_UNBALANCED;
    }
private:
    static int const FLAG_UNBALANCED = -1;
    int treeHeight(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int left = treeHeight(root->left);
        if (left == FLAG_UNBALANCED) {
            return FLAG_UNBALANCED;
        }
        int right = treeHeight(root->right);
        if (right == FLAG_UNBALANCED) {
            return FLAG_UNBALANCED;
        }
        if (std::abs(right - left) > 1) {
            return FLAG_UNBALANCED;
        }
        return std::max(right, left) + 1;
    }
};

