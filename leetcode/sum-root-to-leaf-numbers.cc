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
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
    TreeNode() :
            val(0), left(NULL), right(NULL) {
    }
};

typedef TreeNode* nodeptr;
struct Worker {
    int result;
    Worker() : result(0) {}
    void run(nodeptr curr) {
        if (curr == NULL) {
            return;
        }
        if (!curr->left && !curr->right) {
            result += curr->val;
            return;
        }
        if (curr->left) {
            curr->left->val += curr->val * 10;
            run(curr->left);
        }
        if (curr->right) {
            curr->right->val += curr->val * 10;
            run(curr->right);
        }
    }
};

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        Worker worker;
        worker.run(root);
        return worker.result;
    }
};
static Solution solution;

static int const NODE_COUNT = 13;
TreeNode nodes[13];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i + 1;
    }

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];

    std::cout << solution.sumNumbers(&nodes[0]) << std::endl;
    return 0;
}

