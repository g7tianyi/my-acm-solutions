#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int numDistinct(string text, string word) {
        if (text.empty() || word.empty()) {
            return 0;
        }

        int textlen = text.length(), wordlen = word.length();
        vector<vector<int> > dp;
        for (int i = 0; i < wordlen; ++i) {
            vector<int> v(textlen, 0);
            dp.push_back(v);
        }

        dp[0][0] = text[0] == word[0];
        for (int j = 1; j < textlen; ++j) {
            if (text[j] == word[0]) {
                dp[0][j] = dp[0][j - 1] + 1;
            } else {
                dp[0][j] = dp[0][j - 1];
            }
        }

        for (int i = 1; i < wordlen; ++i) {
            for (int j = i; j < textlen; ++j) {
                if (text[j] == word[i]) {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }

        return dp[wordlen - 1][textlen - 1];
    }
};

Solution solu;

int main() {
    std::cout << solu.numDistinct("rabbbit", "rabbit") << std::endl;
    std::cout << solu.numDistinct("rrabbbit", "rabbit") << std::endl;
    std::cout << solu.numDistinct("rrabbbitttyt", "rabbit") << std::endl;
    std::cout << solu.numDistinct("qrabbbitttytabit", "rabbit") << std::endl;
    std::cout << solu.numDistinct("aaaaa", "aa") << std::endl;
    return 0;
}

