#include <algorithm>
#include <iostream>
#include <deque>

/**
 * Definition for binary tree with next pointer.
 */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode() :
            val(0), left(NULL), right(NULL), next(NULL) {
    }
    TreeLinkNode(int x) :
            val(x), left(NULL), right(NULL), next(NULL) {
    }
};

class Solution {
public:
    typedef TreeLinkNode* nodeptr;
public:
    void connect(TreeLinkNode* root) {
        if (root == NULL) {
            return;
        }
        std::deque<nodeptr> queue;
        queue.push_back(root), queue.push_back(NULL);
        nodeptr curr, next;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop_front();
            if (curr == NULL) {
                if (!queue.empty()) {
                    queue.push_back(NULL);
                }
                continue;
            }
            if (curr->left) {
                queue.push_back(curr->left);
            }
            if (curr->right) {
                queue.push_back(curr->right);
            }
            next = queue.front();
            curr->next = next;
        }
    }
};

Solution solution;

static int const NODE_COUNT = 13;
TreeLinkNode nodes[13];

int main() {
    for (int i = 0; i < NODE_COUNT; ++i) {
        nodes[i].val = i;
    }

    printf("Testing 1: \n");
    solution.connect(&nodes[0]);
    printf("nodes[0]->next = %d\n", nodes[0].next ? nodes[0].next->val : -1);

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9], nodes[5].right = &nodes[10];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];

    printf("\nTesting 2: \n");
    solution.connect(&nodes[0]);
    for (int i = 0; i < NODE_COUNT; ++i) {
        printf("nodes[%d]->next = %d\n", i,
                nodes[i].next ? nodes[i].next->val : -1);
    }

    return 0;
}

