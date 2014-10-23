#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    bool isScramble(string word, string text) {
        int wordlen = word.length(), textlen = text.length();
        if (wordlen != textlen) {
            return false;
        }

        vector<vector<vector<int> > > dp;
        for (int i = 0; i < wordlen; ++i) {
            vector<vector<int> > V;
            for (int j = 0; j < wordlen; ++j) {
                vector<int> v(wordlen + 1);
                V.push_back(v);
            }
            dp.push_back(V);
        }

        for (int i = 0; i < wordlen; i++) {
            for (int j = 0; j < wordlen; j++) {
                dp[i][j][1] = word[i] == text[j];
            }
        }

        for (int k = 2; k <= wordlen; ++k) { // length of the checking range
            for (int i = 0; i + k <= wordlen; ++i) {
                for (int j = 0; j + k <= wordlen; ++j) {
                    for (int p = 1; p < k; ++p) { // p is the split position
                        dp[i][j][k] |= (dp[i][j][p] && dp[i + p][j + p][k - p])
                                || (dp[i][j + k - p][p] && dp[i + p][j][k - p]);
                    }
                }
            }
        }
        return dp[0][0][wordlen];
    }

};

Solution solu;

int main() {
    bool scramble;

    scramble = solu.isScramble("great", "rgtae");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("great", "taerg");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("great", "eatrg");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("great", "grtae");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("great", "rgeat");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("great", "great");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;

    scramble = solu.isScramble("ab", "ba");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("abb", "bab");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;
    scramble = solu.isScramble("abab", "aabb");
    std::cout << (scramble ? "scramble" : "not scramble") << std::endl;

    return 0;
}

