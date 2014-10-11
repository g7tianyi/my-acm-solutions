#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

string result;

struct TRIE {
    int count;
    char letter;
    vector<TRIE*> next;

    TRIE(char _letter) :
            count(1), letter(_letter), next(vector<TRIE*>()) {
    }

    ~TRIE() {
        for (size_t i = 0; i < next.size(); ++i) {
            delete next[i];
        }
        next.clear();
    }

    // the interface is not good, wordCount should not be here
    // don't do it in real life project
    void insert(string& word, int wordCount) {
        TRIE* curr = this;
        size_t i, j, wordlen = word.length();
        for (i = 0; i < wordlen; ++i) {
            bool found = false;
            for (j = 0; j < curr->next.size(); ++j) {
                if (curr->next[j]->letter == word[i]) {
                    ++curr->next[j]->count;
                    if (curr->next[j]->count == wordCount
                            && i + 1 > result.length()) {
                        result = word.substr(0, i + 1);
                    }
                    curr = curr->next[j];
                    found = true;
                    break;
                }
            }
            if (!found) {
                TRIE* newnode = new TRIE(word[i]);
                curr->next.push_back(newnode);
                curr = newnode;
                if (wordCount == 1 && i + 1 > result.length()) {
                    result = word.substr(0, i + 1);
                }
            }
        }
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        TRIE trie('@');
        result.clear();
        int size = strs.size();
        for (int i = 0; i < size; ++i) {
            trie.insert(strs[i], size);
        }
        return result;
    }
};

Solution sol;

int main() {
    string str = "A";
    vector<string> V;
    V.push_back(str);
    std::cout << sol.longestCommonPrefix(V) << std::endl;
    V.clear();
    V.push_back("ABABAAB");
    V.push_back("ABACBAAB");
    V.push_back("ABACBBAB");
    V.push_back("ABAABBAB");
    std::cout << sol.longestCommonPrefix(V) << std::endl;
    return 0;
}

