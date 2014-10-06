
#include <iostream>
#include <vector>

class Solution {
public:
    int numTrees(int n) {
        dp.clear(); // in fact this is not necessary
        dp.resize(n + 1, -1);
        return getNumTrees(n);
    }
private:
    // DP, memorized search
    int getNumTrees(int num) {
        if (num <= 1) {
            return 1;
        }
        if (dp[num] != -1) {
            return dp[num];
        }
        int res = 0;
        for (int i = 1; i <= num; ++i) {
            // i being the rootNode
            // numTrees(i - 1), using numbers [1, i - 1] to get the left subtree
            // numTrees(n - i), using numbers [i + 1, n] to get the right subtree
            res += numTrees(i - 1) * numTrees(num - i);
        }
        dp[num] = res;
        return res;
    }
private:
    std::vector<int> dp;
};

Solution solution;

int main() {
    int numOfNode[] = { 1, 2, 3, 4, 5, 6, 7 };
    for (int i = 0; i < sizeof(numOfNode) / sizeof(int); ++i) {
        printf("Testing with %d node(s) => %d\n", numOfNode[i],
                solution.numTrees(numOfNode[i]));
    }
    return 0;
}

