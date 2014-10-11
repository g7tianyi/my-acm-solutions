#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using std::string;
using std::vector;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> stack;
        int operand1, operand2;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*"
                    || tokens[i] == "/") {
                operand2 = stack.top();
                stack.pop();
                operand1 = stack.top();
                stack.pop();
                stack.push(calculate(operand1, operand2, tokens[i]));
            } else {
                stack.push(stringToInt(tokens[i]));
            }
        }
        if (!stack.empty()) {
            return stack.top();
        }
        return 0;
    }
private:
    inline int calculate(int operand1, int operand2, string& function) {
        if (function == "+") {
            return operand1 + operand2;
        }
        if (function == "-") {
            return operand1 - operand2;
        }
        if (function == "*") {
            return operand1 * operand2;
        }
        return operand1 / operand2;
    }
    inline int stringToInt(const string& str) {
        int result = 0, sign = 1;
        size_t i = 0;
        if (str[0] == '-') {
            sign = -1;
            ++i;
        } else if (str[0] == '+') {
            ++i;
        }
        for (; i < str.size(); ++i) {
            result = result * 10 + (str[i] - '0');
        }
        return result * sign;
    }
};

Solution sol;

int main() {
    vector<string> V;
    V.push_back("2"), V.push_back("1"), V.push_back("+"), V.push_back("3"), V.push_back(
            "*");
    std::cout << sol.evalRPN(V) << std::endl;
    V.clear();
    V.push_back("4"), V.push_back("13"), V.push_back("5"), V.push_back("/"), V.push_back(
            "+");
    std::cout << sol.evalRPN(V) << std::endl;
    return 0;
}

