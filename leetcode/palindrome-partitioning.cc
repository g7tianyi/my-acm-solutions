#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    vector<vector<string> > partition(string str) {
        int size = str.length();
        if (size == 0) {
            vector<vector<string> > result;
            return result;
        }

        vector<vector<bool> > pali;
        for (int i = 0; i < size; ++i) {
            vector<bool> v(size, false);
            v[i] = true;
            pali.push_back(v);
        }
        for (int k = 1; k < size; ++k) {
            for (int i = 0; i + k < size; ++i) {
                if (str[i] == str[i + k]) {
                    pali[i][i + k] = (k == 1) || (pali[i + 1][i + k - 1]);
                }
            }
        }

        return partition(0, size - 1, str, pali);
    }
private:
    vector<vector<string> > partition(int start, int end, string& str,
            vector<vector<bool> >& pali) {
        vector<vector<string> > palindrome;
        if (start == end) {
            vector<string> v;
            string s = str.substr(start, 1);
            v.push_back(s);
            palindrome.push_back(v);
            return palindrome;
        }

        for (int i = start; i <= end; ++i) {
            if (pali[start][i]) {
                vector<vector<string> > right = partition(i + 1, end, str, pali);
                if (!right.empty()) {
                    for (int j = 0; j < right.size(); ++j) {
                        right[j].insert(right[j].begin(), str.substr(start, i - start + 1));
                        palindrome.push_back(right[j]);
                    }
                } else {
                    vector<string> v;
                    v.push_back(str.substr(start, i - start + 1));
                    palindrome.push_back(v);
                }
            }
        }

        return palindrome;
    }
};

Solution solu;

vector<vector<string> > result;

void printResult() {
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    result = solu.partition("aabaabcbcba");
    printResult();

    result = solu.partition("aab");
    printResult();

    result = solu.partition("bb");
    printResult();

    return 0;
}

