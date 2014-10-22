#include <iostream>

#include <cstring>
#include <vector>
using std::vector;

class Solution {
public:
    bool isMatch(const char* text, const char* pattern) {
        if (text == NULL || pattern == NULL) {
            return false;
        }

        int textlen = strlen(text), pattlen = strlen(pattern);
        int count = 0;
        for (int i = 0; i < pattlen; ++i) {
            if (pattern[i] != '*') {
                ++count;
            }
        }
        if (count > textlen) {
            return false;
        }

        vector<vector<bool> > dp;
        for (int i = 0; i < pattlen + 1; ++i) {
            vector<bool> v(textlen + 1, false);
            dp.push_back(v);
        }

        dp[0][0] = true;
        for (int i = 1; i <= pattlen; ++i) {
            if (dp[i - 1][0] && pattern[i - 1] == '*') {
                dp[i][0] = true;
            }
            for (int j = 1; j <= textlen; ++j) {
                if (pattern[i - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else {
                    dp[i][j] = match(text[j - 1], pattern[i - 1]) && dp[i - 1][j - 1];
                }
            }
        }

        return dp[pattlen][textlen];
    }
private:
    inline bool match(char t, char p) {
        return t == p || p == '?';
    }
};

Solution solu;

int main() {
    std::cout << solu.isMatch("aa", "a") << std::endl;
    std::cout << solu.isMatch("aa", "aa") << std::endl;
    std::cout << solu.isMatch("aaa", "*") << std::endl;
    std::cout << solu.isMatch("aa", "*") << std::endl;
    std::cout << solu.isMatch("aa", "a*") << std::endl;
    std::cout << solu.isMatch("ab", "?*") << std::endl;
    std::cout << solu.isMatch("aab", "c*a*b") << std::endl;
    std::cout << solu.isMatch("aabacacc", "a*cc") << std::endl;
    std::cout << solu.isMatch("", "*") << std::endl;
    return 0;
}

