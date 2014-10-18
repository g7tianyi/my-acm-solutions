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
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

typedef TreeNode* nodeptr;

class Solution {
public:
    vector<nodeptr> generateTrees(int n) {
        return generateTrees(1, n);
    }

    vector<nodeptr> generateTrees(int start, int end) {
        vector<nodeptr> trees;
        if (start > end) {
            trees.push_back(NULL);
            return trees;
        }
        if (start == end) {
            trees.push_back(new TreeNode(start));
            return trees;
        }

        for (int i = start; i <= end; ++i) {
            vector<nodeptr> leftTrees = generateTrees(start, i - 1);
            vector<nodeptr> rightTrees = generateTrees(i + 1, end);

            for (size_t j = 0; j < leftTrees.size(); ++j) {
                for (size_t k = 0; k < rightTrees.size(); ++k) {
                    nodeptr root = new TreeNode(i);
                    root->left = leftTrees[j];
                    root->right = rightTrees[k];
                    trees.push_back(root);
                }
            }
        }

        return trees;
    }
};

Solution solu;

int main() {
    return 0;
}

