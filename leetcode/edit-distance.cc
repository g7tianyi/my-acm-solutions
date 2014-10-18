#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int size1 = word1.size(), size2 = word2.size();
        vector<vector<int> > dp;
        for (int i = 0; i <= size1; ++i) {
            vector<int> v(size2 + 1, 1);
            v[0] = i;
            dp.push_back(v);
        }
        for (int i = 0; i <= size2; ++i) {
            dp[0][i] = i;
        }

        for (int i = 1; i <= size1; ++i) {
            for (int j = 1; j <= size2; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // std::min(std::min(delete, insert), replace) + 1
                    dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                }
            }
        }

        return dp[size1][size2];
    }
};

Solution solu;

int main() {
    std::cout << "aaa" << " => " << "aaab" << "\t" << solu.minDistance("aaa", "aaab") << std::endl;
    std::cout << "bge" << " => " << "afge" << "\t" << solu.minDistance("bge", "afge") << std::endl;
    std::cout << "abc" << " => " << "xyz" << "\t" << solu.minDistance("abc", "xyz") << std::endl;
    std::cout << "bcd" << " => " << "bcd" << "\t" << solu.minDistance("bcd", "bcd") << std::endl;
    std::cout << "ab" << " => " << "bc" << "\t" << solu.minDistance("ab", "bc") << std::endl;
    std::cout << "b" << " => " << "" << "\t" << solu.minDistance("b", "") << std::endl;
    return 0;
}

