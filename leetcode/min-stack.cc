#include <stack>

class MinStack {
public:
    void push(int x) {
        values.push(x);
        if (minimums.empty() || minimums.top() >= x) {
            minimums.push(x);
        }
    }

    void pop() {
        if (!minimums.empty() && !values.empty()
                && minimums.top() == values.top()) {
            minimums.pop();
        }
        values.pop();
    }

    int top() {
        return values.top();
    }

    int getMin() {
        return minimums.top();
    }

private:
    std::stack<int> values;
    std::stack<int> minimums;
};

