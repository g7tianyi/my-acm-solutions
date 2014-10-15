#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

#include <deque>

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

class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > result;
        if (root == NULL) {
            return result;
        }

        vector<int> layer;
        std::deque<nodeptr> queue;
        queue.push_back(root), queue.push_back(NULL);
        while (!queue.empty()) {
            nodeptr curr = queue.front();
            queue.pop_front();
            if (curr) {
                layer.push_back(curr->val);
                if (curr->left) {
                    queue.push_back(curr->left);
                }
                if (curr->right) {
                    queue.push_back(curr->right);
                }
            } else {
                if (!queue.empty()) {
                    queue.push_back(NULL);
                }
                vector<int> vec(layer);
                result.push_back(vec);
                layer.clear();
            }
        }

        int numLayer = result.size();
        for (int i = 1; i < numLayer; i += 2) {
            std::reverse(result[i].begin(), result[i].end());
        }

        return result;
    }
};

Solution solu;

TreeNode nodes[7];

int main() {
    nodes[0].val = 3;
    nodes[1].val = 9, nodes[2].val = 20;
    nodes[3].val = 15, nodes[4].val = 7;
    nodes[5].val = 21, nodes[6].val = 16;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[2].left = &nodes[3], nodes[2].right = &nodes[4];
    nodes[3].left = &nodes[5], nodes[4].right = &nodes[6];

    vector<vector<int> > result = solu.zigzagLevelOrder(&nodes[0]);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

