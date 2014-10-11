#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

#include <unordered_set>
using std::unordered_set;

class Solution {
public:
    bool wordBreak(string text, unordered_set<string>& dict) {
        if (text.empty() || dict.empty()) {
            return false;
        }

        vector<int> dp;
        string word;
        for (int i = text.size() - 1; i >= 0; --i) {
            word = text.substr(i);
            if (dict.find(word) != dict.end()) { // try the whole word
                dp.push_back(i);
                continue;
            }
            for (int j = dp.size() - 1; j >= 0; --j) { // DP
                word = text.substr(i, dp[j] - i);
                if (dict.find(word) != dict.end()) {
                    dp.push_back(i);
                    break;
                }
            }
        }

        return !dp.empty() && dp.back() == 0;
    }
};

Solution sol;

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

unordered_set<string> dict;

static void test(string& text) {
    bool breakable = sol.wordBreak(text, dict);
    std::cout << (breakable ? "breakable" : "unbreakable") << std::endl;
}

void test1() {
    dict.clear();
    dict.insert("od");
    dict.insert("le");
    dict.insert("leet");
    dict.insert("code");
    string text = "leetcode";
    test(text);

    dict.clear();
    dict.insert("b");
    text = "a";
    test(text);
}

void test2() {
    dict.clear();
    dict.insert("Given");
    dict.insert("a");
    dict.insert("string");
    dict.insert("s");
    dict.insert("and");
    dict.insert("dictionary");
    dict.insert("of");
    dict.insert("words");
    dict.insert("dict");
    dict.insert("determine");
    dict.insert("if");
    dict.insert("can");
    dict.insert("be");
    dict.insert("segmented");
    dict.insert("into");
    dict.insert("a");
    dict.insert("space");
    dict.insert("separated");
    dict.insert("sequence");
    dict.insert("of");
    dict.insert("one");
    dict.insert("or");
    dict.insert("more");
    string text =
            "Givenastringsandadictionaryofwordsdictdetermineifscanbesegmentedintoaspaceseparatedsequenceofoneormoredictionarywords";
    test(text);
    text =
            "Givenadetermineifscanbesegmentedintoaspaceseparatedstringsandadictionaryofwordsdictsequenceofoneormoredictionarywords";
    test(text);
}

int main() {
    test1();
    test2();
    return 0;
}

