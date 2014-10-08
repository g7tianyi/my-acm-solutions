#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

/**
 * Definition for binary tree
 */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) :
            val(x), left(NULL), right(NULL), next(NULL) {
    }
};

typedef TreeLinkNode* nodeptr;
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) {
            return;
        }

        nodeptr curr = root->next;
        while (curr) {
            if (curr->left) {
                curr = curr->left;
                break;
            }
            if (curr->right) {
                curr = curr->right;
                break;
            }
            curr = curr->next;
        }
        if (root->right) {
            root->right->next = curr;
        }
        if (root->left) {
            root->left->next = root->right ? root->right : curr;
        }

        connect(root->right);
        connect(root->left);
    }
private:
};

