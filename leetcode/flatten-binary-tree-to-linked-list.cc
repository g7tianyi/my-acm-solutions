#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

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

typedef TreeNode* nodeptr;
class Solution {
public:
    void flatten(TreeNode *root) {
        doFlat(root);
    }
private:
    nodeptr doFlat(nodeptr curr) {
        if (curr == NULL) {
            return NULL;
        }
        if (!curr->left && !curr->right) { // leaf node
            return curr;
        }

        nodeptr leftRear = curr->left ? doFlat(curr->left) : NULL;
        nodeptr rightRear = curr->right ? doFlat(curr->right) : leftRear;
        if (leftRear) {
            leftRear->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        return rightRear;
    }
};

static Solution solution;
static int const NODE_COUNT = 13;
TreeNode nodes[NODE_COUNT];

int main() {
    nodes[0].val = 5;
    nodes[1].val = 4;
    nodes[2].val = 8;
    nodes[3].val = 11;
    nodes[4].val = 13;
    nodes[5].val = 4;
    nodes[6].val = 7;
    nodes[7].val = 2;
    nodes[8].val = 5;
    nodes[9].val = 1;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3];
    nodes[2].left = &nodes[4], nodes[2].right = &nodes[5];
    nodes[3].left = &nodes[6], nodes[3].right = &nodes[7];
    nodes[5].left = &nodes[8], nodes[5].right = &nodes[9];

    solution.flatten(&nodes[0]);
    nodeptr curr = &nodes[0];
    while (curr) {
        printf("%d ", curr->val);
        curr = curr->right;
    }
    return 0;
}

