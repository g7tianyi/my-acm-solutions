#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

using std::vector;
using std::deque;

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
class Solution {
public:
    typedef TreeNode* nodeptr;
    TreeNode* sortedArrayToBST(vector<int>& vec) {
        if (vec.empty()) {
            return NULL;
        }
        return sortedArrayToBST(vec, 0, vec.size() - 1);
    }
private:
    nodeptr sortedArrayToBST(vector<int>& vec, int first, int last) {
        if (last < first) {
            return NULL;
        }
        if (last == first) {
            return new TreeNode(vec[first]);
        }
        int middle = mean(first, last);
        nodeptr root = new TreeNode(vec[middle]);
        root->left = sortedArrayToBST(vec, first, middle - 1);
        root->right = sortedArrayToBST(vec, middle + 1, last);
        return root;
    }
    inline int mean(int small, int large) {
        return small + ((large - small) >> 1);
    }
};
static Solution solution;

namespace stest {

static int TEST_SIZE[] = { 7, 8, 15, 16, 17, 1 };
static vector<int> V;
static TreeNode LAYER_TAG(-1);

void mockData(int size) {
    V.clear();
    srand((unsigned) time(0));
    for (int i = 0; i < size; i++) {
        V.push_back(std::abs(100 + rand() % 900));
    }
    std::sort(V.begin(), V.end());
}

void printTree(TreeNode* curr) {
    if (curr == NULL) {
        return;
    }
    deque<TreeNode*> Q;
    Q.push_back(curr), Q.push_back(&LAYER_TAG);
    while (!Q.empty()) {
        TreeNode* curr = Q.front();
        Q.pop_front();

        if (!curr) {
            printf("NIL ");
        } else {
            if (curr->val == -1) {
                if (!Q.empty()) {
                    Q.push_back(&LAYER_TAG);
                }
                printf("\n");
                continue;
            }
            printf("%d ", curr->val);
            Q.push_back(curr->left);
            Q.push_back(curr->right);
        }
    }
}

void deallocate(TreeNode* curr) {
    if (curr == NULL) {
        return;
    }
    if (curr->left) {
        deallocate(curr->left);
    }
    if (curr->right) {
        deallocate(curr->right);
    }
    delete curr;
}

}

int main() {

    for (int i = 0; i < sizeof(stest::TEST_SIZE) / sizeof(int); ++i) {
        printf(">>>>>> Test %d. Size %d\n", i + 1, stest::TEST_SIZE[i]);
        stest::mockData(stest::TEST_SIZE[i]);
        TreeNode* root = solution.sortedArrayToBST(stest::V);
        stest::printTree(root);
        stest::deallocate(root);
    }

    return 0;
}

