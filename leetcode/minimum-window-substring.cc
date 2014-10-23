#include <iostream>
#include <cstring>
#include <string>
#include <deque>
using std::string;

int foundCount[256], textCount[256];

class Solution {
public:
    string minWindow(string text, string word) {

        memset(textCount, 0, sizeof(textCount));
        memset(foundCount, 0, sizeof(foundCount));

        int textlen = text.size(), wordlen = word.size();
        for (int i = 0; i < wordlen; i++) {
            ++textCount[word[i]];
        }

        int found = 0, first = -1, last = textlen;
        std::deque<int> queue;
        for (int i = 0; i < textlen; ++i) {
            if (textCount[text[i]] != 0) {
                queue.push_back(i);
                foundCount[text[i]]++;
                if (foundCount[text[i]] <= textCount[text[i]]) {
                    ++found;
                }
                if (found == wordlen) {
                    int k;
                    do {
                        k = queue.front();
                        queue.pop_front();
                        foundCount[text[k]]--;
                    } while (textCount[text[k]] <= foundCount[text[k]]);
                    if (last - first > i - k) {
                        first = k;
                        last = i;
                    }
                    --found;
                }
            }
        }
        return first != -1 ? text.substr(first, last - first + 1) : "";
    }
};

Solution solu;

int main() {

    std::cout << solu.minWindow("ADOBECODEBANC", "ABC");

    return 0;
}

