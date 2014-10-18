#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_map>

std::unordered_map<int, vector<int> > matching;

struct KMP {
public:
    void match(string& text, string& word, int wordpos) {
        getFail(word);
        int i = 0, j = 0, begin;
        int textlen = text.size(), wordlen = word.size();
        while (i < textlen) {
            if (j == -1 || text[i] == word[j]) {
                ++i, ++j;
                if (j == wordlen) { // find a matched substring for word
                    j = fail[j];

                    begin = i - wordlen;
                    if (matching.find(begin) == matching.end()) {
                        vector<int> index;
                        matching.insert(std::make_pair(begin, index));
                    }
                    matching[begin].push_back(wordpos);
                }
            } else {
                j = fail[j];
            }
        }
    }
private:
    vector<int> fail;
    void getFail(string& word) {
        int size = word.size();
        fail.clear();
        fail.resize(size + 1, -1);
        int i = 0, j = -1;
        while (i < size) {
            if (j == -1 || word[i] == word[j]) {
                fail[++i] = ++j;
            } else {
                j = fail[j];
            }
        }
    }
};

typedef std::unordered_map<int, vector<int> >::iterator HashIter;

class Solution {
public:
    vector<int> findSubstring(string text, vector<string>& words) {
        vector<int> result;
        if (text.size() < words.size()) {
            return result;
        }

        matching.clear();
        KMP kmp;
        for (int i = 0; i < words.size(); ++i) {
            kmp.match(text, words[i], i);
        }

        vector<bool> used(words.size(), false);
        for (HashIter pos = matching.begin(); pos != matching.end(); ++pos) {
            if (search(0, pos->first, used, words)) {
                result.push_back(pos->first);
            }
        }

        return result;
    }
private:
    // curr, current index of the text
    // used, flags indicating if the word of index i has been used for concatenation
    bool search(int depth, int curr, vector<bool>& used, vector<string>& words) {
        if (depth == words.size()) {
            return true;
        }
        HashIter pos = matching.find(curr);
        if (pos == matching.end()) {
            return false;
        }

        bool found;
        vector<int>& index = pos->second;
        for (int i = 0; i < index.size(); ++i) {
            if (used[index[i]]) {
                continue;
            }
            used[index[i]] = true;
            found = search(depth + 1, curr + words[i].size(), used, words);
            used[index[i]] = false;
            if (found) {
                return true;
            }
        }
        return false;
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

    S = "aabaaababaa";
    L.clear(), L.push_back("a"), L.push_back("aa");
    result = solu.findSubstring(S, L);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

