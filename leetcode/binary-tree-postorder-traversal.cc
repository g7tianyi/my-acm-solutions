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

#include <stack>
class Solution {
public:
    typedef TreeNode* nodeptr;
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> V;
        if (root == NULL) {
            return V;
        }

        // we can just use std::reverse()
        // but with stack, the code is much more self-explanatory
        std::stack<nodeptr> stack;
        std::stack<int> value;
        stack.push(root);
        while (!stack.empty()) {
            nodeptr curr = stack.top();
            stack.pop();
            value.push(curr->val);
            if (curr->left) {
                stack.push(curr->left);
            }
            if (curr->right) {
                stack.push(curr->right);
            }
        }

        while (!value.empty()) {
            V.push_back(value.top());
            value.pop();
        }

        return V;
    }
};
static Solution solution;

namespace stest {
static int const NODE_COUNT = 13;
TreeNode nodes[13];

void mockData1() {
    memset(nodes, 0, sizeof(nodes));
    for (int i = 0; i <= NODE_COUNT; ++i) {
        nodes[i].val = i + 1;
    }
    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3], nodes[1].right = &nodes[4];
    nodes[2].left = &nodes[5], nodes[2].right = &nodes[6];
    nodes[3].left = &nodes[7], nodes[3].right = &nodes[8];
    nodes[4].left = &nodes[9], nodes[5].right = &nodes[10];
    nodes[6].left = &nodes[11], nodes[6].right = &nodes[12];
}

void mockData2() {
    memset(nodes, 0, sizeof(nodes));
    nodes[0].val = 3;
    nodes[1].val = 2;
    nodes[2].val = 4;
    nodes[5].val = 1;
    nodes[0].left = &nodes[1];
    nodes[0].right = &nodes[2];
    nodes[2].left = &nodes[5];
}

void test1() {
    mockData1();
    vector<int> V = solution.postorderTraversal(&nodes[0]);
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void test2() {
    mockData2();
    vector<int> V = solution.postorderTraversal(&nodes[0]);
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

}

int main() {
    stest::test1();
    stest::test2();
    return 0;
}

