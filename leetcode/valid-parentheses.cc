#include <stack>
#include <string>
using std::string;
class Solution {
public:
    bool isValid(string str) {
        if (str.length() == 0) {
            return false;
        }
        std::stack<char> stack;
        int length = str.length();
        char curr, pair;
        for (int i = 0; i < length; ++i) {
            curr = str.at(i);
            pair = getPair(curr);
            if (stack.empty() || stack.top() != pair) {
                stack.push(curr);
            } else {
                stack.pop();
            }
        }
        return stack.empty();
    }
private:
    inline char getPair(char ch) {
        if (ch == ')') {
            return '(';
        }
        if (ch == '}') {
            return '{';
        }
        if (ch == ']') {
            return '[';
        }
        return '@';
    }
};

