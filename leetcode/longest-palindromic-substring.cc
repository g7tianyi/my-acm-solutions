#include <iostream>
#include <string>
using std::string;

bool pali[1001][1001];

class Solution {
public:
    string longestPalindrome(string str) {
        string result;
        if (str.empty()) {
            return result;
        }

        memset(pali, 0, sizeof(pali));
        int size = str.size();
        for (int i = 0; i < size; ++i) {
            pali[i][i] = true;
        }

        int resi = 0, resk = 0, maxlen = 0;
        for (int k = 1; k < size; ++k) { // length
            for (int i = 0; i + k < size; ++i) { // start => i, end => i + k
                if (str[i] == str[i + k]) {
                    pali[i][i + k] = (k == 1) || (pali[i + 1][i + k - 1]);
                    if (pali[i][i + k]) {
                        maxlen = k, resi = i, resk = k;
                    }
                }
            }
        }

        result = str.substr(resi, resk + 1);
        return result;
    }
};

Solution solu;

#include <ctime>

int myrandom(int i) {
    return std::rand() % i;
}

int main() {
    std::cout << solu.longestPalindrome("aab") << std::endl;
    std::cout << solu.longestPalindrome("aabaabcbcba") << std::endl;
    std::cout << solu.longestPalindrome("abcdefghijklmnopqrstuvwxyz") << std::endl;
    return 0;
}

