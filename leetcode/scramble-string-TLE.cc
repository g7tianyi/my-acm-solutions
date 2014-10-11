#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    typedef string::iterator iterator;
    bool isScramble(string word, string text) {
        if (word.size() != text.size()) {
            return false;
        }
        if (word.empty()) {
            return true;
        }
        if(isScramble(word.begin(), word.end(), text.begin(), text.end())) {
            return true;
        }
        std::reverse(word.begin(), word.end());
        return isScramble(word.begin(), word.end(), text.begin(), text.end());
    }

private:
    bool isScramble(iterator wBegin, iterator wEnd, iterator tBegin, iterator tEnd) {

        int length = wEnd - wBegin;
        if (length == 1) {
            return *wBegin == *tBegin;
        }

        for (int i = 1; i < length; ++i) {
            // all standard
            bool formerStandard = isScramble(wBegin, wBegin + i, tBegin, tBegin + i);
            bool latterStandard = isScramble(wBegin + i, wEnd, tBegin + i, tEnd);

            if (formerStandard && latterStandard) {
                return true;
            }

            // the former part is reversed
            std::reverse(tBegin, tBegin + i);
            bool formerReversed = isScramble(wBegin, wBegin + i, tBegin, tBegin + i);
            std::reverse(tBegin, tBegin + i);

            if (formerReversed && latterStandard) {
                return true;
            }

            // the latter part is reversed
            std::reverse(tBegin + i, tEnd);
            bool latterReversed = isScramble(wBegin + i, wEnd, tBegin + i, tEnd);
            std::reverse(tBegin + i, tEnd);

            if (formerStandard && latterReversed) {
                return true;
            }

            // all reversed
            if (formerReversed && latterReversed) {
                return true;
            }
        }

        return false;
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

