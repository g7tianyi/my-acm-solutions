#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Definition for binary tree
 */
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

class Solution {
public:
    typedef TreeNode* nodeptr;
    bool isSymmetric(TreeNode *root) {
        if (!root) {
            return true;
        }
        return isSymmetric(root->left, root->right);
    }
private:
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        if (!left && !right) {
            return true;
        }
        if ((left && !right) || (!left && right) || left->val != right->val) {
            return false;
        }
        return isSymmetric(left->left, right->right)
                && isSymmetric(left->right, right->left);
    }
};
static Solution solution;

namespace stest {
TreeNode nodes[7];

void setUpTest1() {
    memset(nodes, 0, sizeof(nodes));

    nodes[0] = 1, nodes[1] = 2, nodes[2] = 3;
    nodes[3] = 3, nodes[5] = 2;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3];
    nodes[2].left = &nodes[5];
}

void setUpTest2() {
    memset(nodes, 0, sizeof(nodes));

    nodes[0] = 1;
    nodes[1] = 2, nodes[2] = 2;
    nodes[3] = 3, nodes[4] = 4;
    nodes[5] = 4, nodes[6] = 3;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
}

}

int main() {
    using namespace stest;
    setUpTest1();
    printf("Test 1: %c\n", solution.isSymmetric(&nodes[0]) ? 'Y' : 'N');
    setUpTest2();
    printf("Test 2: %c\n", solution.isSymmetric(&nodes[0]) ? 'Y' : 'N');
    return 0;
}

