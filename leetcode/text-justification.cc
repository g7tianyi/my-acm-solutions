#include <iostream>
#include <vector>
using std::vector;
#include <string>
using std::string;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int L) {
        vector<string> result;
        if (words.empty()) {
            return result;
        }

        int size = words.size();
        int nWord = 0, nLength = 0;
        for (int i = 0; i < size; ++i) {
            if (words[i].length() + nLength + nWord > L) {
                string line = concat(words, i - nWord, nWord, nLength, L);
                result.push_back(line);
                nWord = 1;
                nLength = words[i].length();
            } else {
                ++nWord;
                nLength += words[i].length();
            }
        }

        if (nWord) {
            string line = concat(words, size - nWord, nWord, nLength, L);
            result.push_back(line);
        }

        if (!result.empty()) {
            string& last = result.back();
            int i = 0, j = 0;
            while (i < last.size()) {
                if (last[i] == ' ' && i > 0 && last[i - 1] == ' ') {
                    break;
                }
                ++i;
            }
            j = i;
            while (i < last.size()) {
                if (last[i] != ' ' || (i > 0 && last[i - 1] != ' ')) {
                    last[j++] = last[i];
                }
                ++i;
            }
            while (j < last.size()) {
                last[j++] = ' ';
            }
        }

        return result;
    }
private:
    string concat(vector<string>& words, int start, int nWord, int nLength, int L) {
        string line;
        int nSpace = L - nLength;
        if (nWord == 1) {
            line += words[start];
            for (int k = 0; k < nSpace; ++k) {
                line += ' ';
            }
        } else {
            int div = nSpace / (nWord - 1);
            int mod = nSpace % (nWord - 1);
            for (int k = 0; k < nWord; ++k) {
                line += words[start + k];
                if (k != nWord - 1) {
                    for (int p = 0; p < div; ++p) {
                        line += ' ';
                    }
                    if (k < mod) {
                        line += ' ';
                    }
                }
            }
        }
        return line;
    }
};

Solution solu;

int main() {
    vector<string> words;

    words.push_back("This"), words.push_back("is"), words.push_back("an");
    words.push_back("example"), words.push_back("of"), words.push_back("text");
    words.push_back("justification"), words.push_back("justification.");
    words.push_back("a"), words.push_back("aa"), words.push_back("aaa");
    words.push_back("aaaa"), words.push_back("aaaaa"), words.push_back("aaaaaa");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("b"), words.push_back("b"), words.push_back("b");
    words.push_back("stupid"), words.push_back("req"), words.push_back("ll");

    vector<string> result;
    result = solu.fullJustify(words, 16);
    for (int i = 0; i < result.size(); ++i) {
        printf("[%s]\n", result[i].c_str());
    }
    printf("------------------\n");

    words.clear();
    words.push_back("");
    result = solu.fullJustify(words, 0);
    for (int i = 0; i < result.size(); ++i) {
        printf("[%s]\n", result[i].c_str());
    }
    printf("------------------\n");

    words.clear();
    // ["What","must","be","shall","be."], 12
    words.push_back("What"), words.push_back("must"), words.push_back("be");
    words.push_back("shall"), words.push_back("be.");
    result = solu.fullJustify(words, 12);
    for (int i = 0; i < result.size(); ++i) {
        printf("[%s]\n", result[i].c_str());
    }
    printf("------------------\n");

    return 0;
}

