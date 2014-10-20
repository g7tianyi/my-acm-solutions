#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_set>
#include <unordered_map>
using std::unordered_set;
using std::unordered_map;

unordered_map<int, vector<string> > dp;

class Solution {
public:
    vector<string> wordBreak(string text, unordered_set<string>& dict) {
        dp.clear();
        return wordBreak(text, 0, dict);
    }
private:
    vector<string> wordBreak(string& text, int curr, unordered_set<string>& dict) {
        vector<string> result, half;
        string word;
        for (int i = 1; i + curr <= text.size(); ++i) {
            word = text.substr(curr, i);
            if (dict.find(word) != dict.end()) {
                if (curr + i == text.size()) { // end of recursion
                    result.push_back(word);
                    break;
                }

                if (dp.find(curr + i) == dp.end()) {
                    dp[curr + i] = wordBreak(text, curr + i, dict);
                }
                half = dp[curr + i];
                if (!half.empty()) {
                    for (vector<string>::iterator pos = half.begin(); pos != half.end(); ++pos) {
                        result.push_back(word + " " + *pos);
                    }
                }
            }
        }
        return result;
    }
};

Solution solu;

int main() {
    string text;
    vector<string> result;
    unordered_set<string> dict;
    dict.insert("cat"), dict.insert("cats"), dict.insert("and");
    dict.insert("dog"), dict.insert("sand");

    text = "catsanddog";
    result = solu.wordBreak(text, dict);
    std::copy(result.begin(), result.end(), std::ostream_iterator<string>(std::cout, "\n"));
    std::cout << std::endl;

    return 0;
}

