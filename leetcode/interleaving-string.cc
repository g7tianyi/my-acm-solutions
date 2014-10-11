#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.empty()) {
            return s2.compare(s3) == 0;
        }
        if (s2.empty()) {
            return s1.compare(s3) == 0;
        }

        int size1 = s1.size(), size2 = s2.size(), size3 = s3.size();
        if (size1 + size2 != size3) {
            return false;
        }

        vector<vector<bool> > dp;
        for (int i = 0; i < size1 + 1; ++i) {
            vector<bool> v(size2 + 1, false);
            dp.push_back(v);
        }

        dp[1][0] = s1[0] == s3[0];
        for (int i = 2; i <= size1; ++i) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }

        dp[0][1] = s2[0] == s3[0];
        for (int i = 2; i <= size2; ++i) {
            dp[0][i] = dp[0][i - 1] && (s2[i - 1] == s3[i - 1]);
        }

        for (int i = 1; i <= size1; ++i) {
            for (int j = 1; j <= size2; ++j) {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1])
                        || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }

        return dp[size1][size2];
    }
};

Solution solu;

int main() {
    bool isInterleave;
    isInterleave = solu.isInterleave("aabcc", "dbbca", "aadbbcbcac");
    std::cout << (isInterleave ? "is interleave" : "is not interleave")
            << std::endl;
    isInterleave = solu.isInterleave("aabcc", "dbbca", "aadbbbaccc");
    std::cout << (isInterleave ? "is interleave" : "is not interleave")
            << std::endl;
    isInterleave = solu.isInterleave("a", "", "a");
    std::cout << (isInterleave ? "is interleave" : "is not interleave")
            << std::endl;
    return 0;
}

