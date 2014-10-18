#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_map>

class Solution {
public:
    vector<int> findSubstring(string text, vector<string>& words) {
        vector<int> result;
        int wordlen = words[0].size();
        int textlen = wordlen * words.size();
        if (textlen > text.size()) {
            return result;
        }

        std::unordered_map<string, int> count;
        for (int i = 0; i < words.size(); i++) {
            ++count[words[i]];
        }

        int begin = 0;
        std::unordered_map<string, int> used;
        while (begin <= text.size() - textlen) {
            bool found = true;
            used.clear();
            for (int i = begin; i <= begin + wordlen * (words.size() - 1); i += wordlen) {
                string curr = text.substr(i, wordlen);
                if ((count.find(curr) == count.end())
                        || (used[curr] == count[curr])) {
                    found = false;
                    break;
                }
                ++used[curr];
            }
            if (found) {
                result.push_back(begin);
            }
            ++begin;
        }

        return result;
    }
};

Solution solu;

int main() {

    string S;
    vector<string> L;
    vector<int> result;

    S = "barfoothefoobarman";
    L.push_back("foo"), L.push_back("bar");
    result = solu.findSubstring(S, L);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    S = "aaa";
    L.clear(), L.push_back("a"), L.push_back("a");
    result = solu.findSubstring(S, L);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    S = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    L.clear(), L.push_back("fooo"), L.push_back("barr"), L.push_back("wing"), L.push_back("ding"), L.push_back(
            "wing");
    result = solu.findSubstring(S, L);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

