#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

#define __LOCAL_MODE__
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
    typedef vector<int>::iterator iterator;
    TreeNode* buildTree(vector<int>& inOrder, vector<int>& postOrder) {
        return buildTree(inOrder.begin(), inOrder.end(), postOrder.begin(),
                postOrder.end());
    }
private:
    TreeNode* buildTree(iterator inOrderBegin, iterator inOrderEnd,
            iterator postOrderBegin, iterator postOrderEnd) {

        if (inOrderBegin == inOrderEnd || postOrderBegin == postOrderEnd) {
            return NULL;
        }

        int value = *(postOrderEnd - 1);
        TreeNode* root = new TreeNode(value);

        iterator pos = std::find(inOrderBegin, inOrderEnd, value);
        int leftSize = pos - inOrderBegin;

        iterator leftInOrderBegin    = inOrderBegin;
        iterator leftInOrderEnd      = pos;
        iterator rightInOrderBegin   = pos + 1;
        iterator rightInOrderEnd     = inOrderEnd;

        iterator leftPostOrderBegin  = postOrderBegin;
        iterator leftPostOrderEnd    = postOrderBegin + leftSize;
        iterator rightPostOrderBegin = postOrderBegin + leftSize;
        iterator rightPostOrderEnd   = postOrderEnd - 1;

        root->left = buildTree(leftInOrderBegin, leftInOrderEnd,
                leftPostOrderBegin, leftPostOrderEnd);
        root->right = buildTree(rightInOrderBegin, rightInOrderEnd,
                rightPostOrderBegin, rightPostOrderEnd);

        return root;
    }
};

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

vector<vector<int> > V;

void print(vector<int> V) {
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {

    vector<int> coll;
    coll.push_back(4), coll.push_back(2), coll.push_back(5);
    coll.push_back(6), coll.push_back(3), coll.push_back(1);

    print(coll);
    vector<int>::iterator pos = std::find(coll.begin(), coll.end(), 3);
    int size = pos - coll.begin();
    std::cout << size << std::endl;
    print(vector<int>(coll.begin(), coll.begin() + size));
    print(vector<int>(coll.begin() + size, coll.end() - 1));

    return 0;
}

