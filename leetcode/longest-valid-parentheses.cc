#include <algorithm>
#include <iostream>

#include <stack>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Solution {
public:
    int longestValidParentheses(string text) {
        int len = text.size();
        if (len < 2) {
            return 0;
        }

        vector<int> match(len + 1, -1), dp(len + 1, 0);
        std::stack<int> stack;
        int i, j = 0;
        while (j != len) {
            if (stack.empty() || text[j] == '(') {
                stack.push(j);
            } else {
                i = stack.top();
                if (text[i] == '(') {
                    stack.pop();
                    match[j] = i;
                } else {
                    stack.push(j);
                }
            }
            ++j;
        }
        stack.empty();

        // dp(j), the max length preciously ending in j
        // strictly, dp(j) = dp(k) + (j-k+1), where k is the matching pos of j
        int result = 0;
        for (j = 1; j < len; ++j) {
            i = match[j];
            if (i != -1 && i < j) { // has a matching pos which lies before j
                dp[j] = (i > 0 ? dp[i - 1] : 0) + (j - i + 1);
                result = std::max(result, dp[j]);
            }
        }

        return result;
    }
};

Solution solu;

int main() {

    vector<string> texts;
    texts.push_back("(("), texts.push_back("()"), texts.push_back("(()");
    texts.push_back(")()())"), texts.push_back(")((()))()(()()())))");
    texts.push_back("()())()()(((()))))))");
    texts.push_back("()()()(())((()))()(()()())))");
    for (int i= 0; i < texts.size(); ++i) {
        std::cout << texts[i] << " => " << solu.longestValidParentheses(texts[i]) << std::endl;
    }
    return 0;
}

