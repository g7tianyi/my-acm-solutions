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

#include <deque>
using std::deque;

class Solution {
public:
    typedef TreeNode* nodeptr;
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > V;
        if (root == NULL) {
            return V;
        }

        int index = 0;
        vector<int> C;
        V.push_back(C);

        deque<nodeptr> queue;
        queue.push_back(root);
        queue.push_back(NULL);
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

        std::reverse(V.begin(), V.end());
        return V;
    }
};
static Solution solution;

static int const NODE_COUNT = 13;
TreeNode nodes[13];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i;
    }
    // TODO: implement a test utility to randomly generate a binary tree
    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9], nodes[5].right = &nodes[10];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];

    vector<vector<int> > V = solution.levelOrderBottom(&nodes[0]);
    int size = V.size();
    for (int i = 0; i < V.size(); ++i) {
        std::copy(V[i].begin(), V[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

