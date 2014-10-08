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
};

#include <deque>

class Solution {
public:
    typedef TreeNode* nodeptr;
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL) {
            return false;
        }

        std::deque<nodeptr> queue;
        queue.push_back(root);
        while (!queue.empty()) {
            nodeptr curr = queue.front();
            queue.pop_front();

            if (!curr->left && !curr->right && curr->val == sum) {
                return true;
            }
            if (curr->left) {
                curr->left->val += curr->val;
                queue.push_back(curr->left);
            }
            if (curr->right) {
                curr->right->val += curr->val;
                queue.push_back(curr->right);
            }
        }
        return false;
    }
};

