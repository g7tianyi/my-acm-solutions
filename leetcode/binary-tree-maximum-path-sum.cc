#include <algorithm>
#include <iostream>

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
    TreeNode() :
            val(0), left(NULL), right(NULL) {
    }
};

struct Worker {
    int maxSum;
    Worker(int maxSum_) :
            maxSum(maxSum_) {
    }

    int run(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        int leftMax = run(root->left);
        int rightMax = run(root->right);
        int nodeMax = root->val
                + (leftMax > 0 ? leftMax : 0)
                + (rightMax > 0 ? rightMax : 0);
        int sonMax = std::max(leftMax, rightMax);
        if (maxSum < nodeMax) {
            maxSum = nodeMax;
        }
        return root->val + (sonMax > 0 ? sonMax : 0);
    }
};

class Solution {
public:
    int maxPathSum(TreeNode *root) {
        if (root == NULL) {
            return 0;
        }
        Worker worker(root->val);
        worker.run(root);
        return worker.maxSum;
    }
};

Solution solu;

TreeNode nodes[10];

int main() {

    nodes[0].val = 8, nodes[1].val = 9, nodes[2].val = -8;
    nodes[3].val = 3, nodes[4].val = -6, nodes[5].val = 9;
    nodes[6].val = 7, nodes[7].val = -4, nodes[8].val = -1;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[4], nodes[2].right = &nodes[5];
    nodes[5].left = &nodes[7], nodes[5].right = &nodes[8];

    std::cout << solu.maxPathSum(&nodes[0]) << std::endl;

    //////

    nodes[0].val = -8, nodes[1].val = -9, nodes[2].val = -8;
    nodes[3].val = -3, nodes[4].val = -6, nodes[5].val = 9;
    nodes[6].val = -7, nodes[7].val = -4, nodes[8].val = 1;
    std::cout << solu.maxPathSum(&nodes[0]) << std::endl;

    return 0;
}

