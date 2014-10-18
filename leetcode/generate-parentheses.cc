#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

struct Runner {
    int count, leftCount, rightCount;
    vector<string>& result;
    Runner(int n, vector<string>& _result) :
            count(n << 1), leftCount(n), rightCount(n), result(_result) {
    }

    void run(string& curr) {
        if (leftCount == 0 && rightCount == 0) {
            string str(curr);
            result.push_back(str);
            return;
        }

        if (leftCount) {
            curr += '(';
            --leftCount;
            run(curr);
            ++leftCount;
            curr.erase(curr.end() - 1);
        }
        if (rightCount > leftCount) {
            curr += ')';
            --rightCount;
            run(curr);
            ++rightCount;
            curr.erase(curr.end() - 1);
        }

    }
};

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        Runner runner(n, result);
        string str;
        runner.run(str);
        return result;
    }
};

Solution solu;

int main() {
    vector<string> result;
    for (int i = 1; i <= 10; ++i) {
        result = solu.generateParenthesis(i);
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i] << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}

