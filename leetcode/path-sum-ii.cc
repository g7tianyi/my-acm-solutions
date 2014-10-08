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


typedef TreeNode* nodeptr;
struct Worker {
public:
    Worker(vector<vector<int> >& v) :
            result(v) {
    }
    void run(nodeptr curr, int sum) {
        vector<int> V;
        V.push_back(curr->val);
        run(curr, sum, V);
    }
private:
    void run(nodeptr curr, int sum, vector<int>& V) {
        if (!curr->left && !curr->right && curr->val == sum) {
            vector<int> R(V);
            result.push_back(R);
        }
        if (curr->left) {
            V.push_back(curr->left->val);
            curr->left->val += curr->val;
            run(curr->left, sum, V);
            V.pop_back();
        }
        if (curr->right) {
            V.push_back(curr->right->val);
            curr->right->val += curr->val;
            run(curr->right, sum, V);
            V.pop_back();
        }
    }
private:
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > result;
        if (root == NULL) {
            return result;
        }
        Worker worker(result);
        worker.run(root, sum);
        return result;
    }
};

static Solution solution;
static int const NODE_COUNT = 13;
TreeNode nodes[NODE_COUNT];

int main() {
    nodes[0].val = 5;  nodes[1].val = 4;  nodes[2].val = 8;
    nodes[3].val = 11; nodes[4].val = 13; nodes[5].val = 4;
    nodes[6].val = 7;  nodes[7].val = 2;  nodes[8].val = 5;
    nodes[9].val = 1;

    nodes[0].left = &nodes[1], nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3];
    nodes[2].left = &nodes[4], nodes[2].right = &nodes[5];
    nodes[3].left = &nodes[6], nodes[3].right = &nodes[7];
    nodes[5].left = &nodes[8], nodes[5].right = &nodes[9];

    vector<vector<int> > V = solution.pathSum(&nodes[0], 22);
    int size = V.size();
    for (int i = 0; i < size; ++i) {
        std::copy(V[i].begin(), V[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

