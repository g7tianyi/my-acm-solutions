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
        if (pattlen == 0) {
            return textlen == 0;
        }

        vector<vector<bool> > dp;
        for (int i = 0; i <= textlen; ++i) {
            vector<bool> v(pattlen + 1, false);
            dp.push_back(v);
        }

        // dp(i,j),
        // matching status of using first i elements of text
        // and first j elements of pattern
        dp[0][0] = true;
        for (int j = 0; j < pattlen; ++j) {
            if (pattern[j] == '*') {
                if (j == 0) { // '*' has no preceding element, skip
                    continue;
                }
                if (dp[0][j - 1]) {
                    // T: aaaaaaa
                    // P: ac*
                    dp[0][j + 1] = true;
                }
                if (pattern[j - 1] != '.') {
                    for (int i = 0; i < textlen; i++) {
                        if (dp[i + 1][j]
                            //        i
                            // T: aaaababbaaa
                            // P:   a*ba*
                            //          j (match the previous 'a' for one time)
                            || (j > 0 && dp[i + 1][j - 1])
                            //         j
                            // T: aaabcdefg
                            // P:  a*bcf*
                            //          i (match f for zero time)
                            || (i > 0 && j > 0
                                      && dp[i][j + 1]
                                      && text[i] == text[i - 1]
                                      && text[i - 1] == pattern[j - 1])
                            //            i
                            // T: aaaabcddd
                            // P:   a*bcdd*
                            //            j
                        ) {
                            dp[i + 1][j + 1] = true;
                        }
                    }
                } else {
                    int i = 0;
                    while (j > 0 && i < textlen
                                 && !dp[i + 1][j - 1] && !dp[i + 1][j]) {
                        ++i;
                    }
                    for (; i < textlen; i++) {
                        dp[i + 1][j + 1] = true;
                    }
                }
            } else {
                for (int i = 0; i < textlen; i++) {
                    dp[i + 1][j + 1] = dp[i][j]
                            && (text[i] == pattern[j] || pattern[j] == '.');
                }
            }
        }
        return dp[textlen][pattlen];
    }
};

Solution solu;

int main() {
    std::cout << solu.isMatch("aa", "a") << std::endl;
    std::cout << solu.isMatch("aa", "aa") << std::endl;
    std::cout << solu.isMatch("aaa", "*") << std::endl;
    std::cout << solu.isMatch("aa", "*") << std::endl;
    std::cout << solu.isMatch("aa", "a*") << std::endl;
    std::cout << solu.isMatch("ab", ".*") << std::endl;
    std::cout << solu.isMatch("aab", "c*a*b") << std::endl;
    std::cout << solu.isMatch("aabacacc", "a*cc") << std::endl;
    std::cout << solu.isMatch("", "*") << std::endl;
    return 0;
}

