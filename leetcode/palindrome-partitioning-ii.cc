#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int minCut(string str) {
        if (str.empty()) {
            return 0;
        }

        int size = str.length();
        vector<vector<bool> > pali;
        vector<vector<int> > dp;
        for (int i = 0; i < size; ++i) {
            vector<bool> vb(size, false);
            vb[i] = true;
            pali.push_back(vb);
            vector<int> vi(size, -1);
            dp.push_back(vi);
        }
        for (int k = 1; k < size; ++k) {
            for (int i = 0; i + k < size; ++i) {
                if (str[i] == str[i + k]) {
                    pali[i][i + k] = (k == 1) || (pali[i + 1][i + k - 1]);
                }
            }
        }

        return minCut(0, size - 1, pali, dp);
    }
private:
    int minCut(int start, int end, vector<vector<bool> >& pali, vector<vector<int> >& dp) {
        if (dp[start][end] != -1) {
            return dp[start][end];
        }

        if (pali[start][end]) {
            dp[start][end] = 0;
            return 0;
        }

        int result = end - start;
        for (int i = start; i <= end; ++i) {
            if (pali[start][i]) {
                result = std::min(result, minCut(i + 1, end, pali, dp) + 1);
            }
        }
        dp[start][end] = result;
        return result;
    }
};

Solution solu;

int main() {
    std::cout << solu.minCut("bb") << std::endl;
    std::cout << solu.minCut("aab") << std::endl;
    std::cout << solu.minCut("aabaabcbcba") << std::endl;
    std::cout << solu.minCut("abcdefghijklmnopqrstuvwxyz") << std::endl;
    std::cout << solu.minCut("aaabaa") << std::endl;
    return 0;
}

