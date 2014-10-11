#include <limits>
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        // unsafe code, if the leftmost code is INT_MIN, we are doomed
        return isValidBST(root, std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max());
    }
private:
    bool isValidBST(TreeNode* root, int leftValue, int rightValue) {
        if (root == NULL) {
            return true;
        }

        if (root->val <= leftValue || root->val >= rightValue) {
            return false;
        }

        return isValidBST(root->left, leftValue, root->val)
                && isValidBST(root->right, root->val, rightValue);
    }
};

