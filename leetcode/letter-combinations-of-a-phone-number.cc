#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

const char lettermap[10][4] = {
    { '@', '@', '@', '@' }, { '@', '@', '@', '@' }, // 0 1
    { 'a', 'b', 'c', '@' }, { 'd', 'e', 'f', '@' }, // 2 3
    { 'g', 'h', 'i', '@' }, { 'j', 'k', 'l', '@' }, // 4 5
    { 'm', 'n', 'o', '@' }, { 'p', 'q', 'r', 's' }, // 6 7
    { 't', 'u', 'v', '@' }, { 'w', 'x', 'y', 'z' }, // 8 9
};

struct Worker {
    Worker(string& digits_, vector<string>& result_) :
            digits(digits_), result(result_) {
    }

    void run(int pos, string& word) {
        if (pos == digits.size()) {
            result.push_back(word);
            return;
        }
        char ch = digits[pos];
        for (int i = 0; i < 4; ++i) {
            if (lettermap[ch - '0'][i] != '@') {
                word.push_back(lettermap[ch - '0'][i]);
                run(pos + 1, word);
                word.pop_back();
            }
        }
    }
    string& digits;
    vector<string>& result;
};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty()) {
            result.push_back("");
            return result;
        }
        Worker worker(digits, result);
        string word;
        worker.run(0, word);
        return result;
    }
};

Solution solu;

int main() {
    vector<string> combinations = solu.letterCombinations("23");
    std::copy(combinations.begin(), combinations.end(),
            std::ostream_iterator<string>(std::cout, "\n"));
    return 0;
}

