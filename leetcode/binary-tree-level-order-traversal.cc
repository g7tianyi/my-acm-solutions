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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > V;
        if (root == NULL) {
            return V;
        }

        std::deque<nodeptr> queue;
        queue.push_back(root);
        queue.push_back(NULL);
        int index = 0;
        vector<int> C;
        V.push_back(C);
        while (!queue.empty()) {
            nodeptr curr = queue.front();
            queue.pop_front();

            if (curr) {
                V[index].push_back(curr->val);
                if (curr->left) {
                    queue.push_back(curr->left);
                }
                if (curr->right) {
                    queue.push_back(curr->right);
                }
            } else {
                if (!queue.empty()) {
                    queue.push_back(NULL);
                    vector<int> C;
                    V.push_back(C);
                    ++index;
                }
            }
        }
        return V;
    }
};


