#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

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

typedef TreeNode* nodeptr;
class Solution {
public:
    int minDepth(TreeNode *root) {
        if (root == NULL) {
            return 0;
        }

        std::deque<nodeptr> queue;
        queue.push_back(root);
        queue.push_back(NULL);
        int depth = 1;
        while (!queue.empty()) {
            nodeptr curr = queue.front();
            queue.pop_front();
            if (curr) {
                if (!curr->left && !curr->right) {
                    break;
                }
                if (curr->left) {
                    queue.push_back(curr->left);
                }
                if (curr->right) {
                    queue.push_back(curr->right);
                }
            } else {
                if (!queue.empty()) {
                    ++depth;
                    queue.push_back(NULL);
                }
            }
        }
        return depth;
    }
};

static Solution solution;
static int const NODE_COUNT = 13;
static TreeNode nodes[13];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i;
    }

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];
    printf("%d\n", solution.minDepth(&nodes[0]));

    nodes[3].left = NULL, nodes[3].right = NULL;
    printf("%d\n", solution.minDepth(&nodes[0]));

    nodes[2].left = NULL, nodes[2].right = NULL;
    printf("%d\n", solution.minDepth(&nodes[0]));

    nodes[1].left = NULL, nodes[1].right = NULL;
    printf("%d\n", solution.minDepth(&nodes[0]));

    nodes[0].left = NULL, nodes[0].right = NULL;
    printf("%d\n", solution.minDepth(&nodes[0]));

    printf("%d\n", solution.minDepth(NULL));

    return 0;
}

