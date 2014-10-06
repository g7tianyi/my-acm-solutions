#include <algorithm>
#include <iostream>
#include <vector>
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

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> vec;
        traverse(root, vec);
        return vec;
    }
private:
    void traverse(TreeNode* curr, vector<int>& vec) {
        if (curr == NULL) {
            return;
        }
        traverse(curr->left, vec);
        vec.push_back(curr->val);
        traverse(curr->right, vec);
    }
};

Solution solution;

static int const NODE_COUNT = 13;
TreeNode nodes[13];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i;
    }

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9], nodes[5].right = &nodes[10];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];

    vector<int> vec = solution.inorderTraversal(&nodes[0]);
    std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    nodes[4].right = &nodes[6], nodes[2].right = NULL;
    vec = solution.inorderTraversal(&nodes[0]);
    std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

