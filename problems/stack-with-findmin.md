支持findMin的棧
====
來自Mark Allen Weiss叔叔書上的習題：

> Propose a data structure that supports the stack push and pop operations and a third operation findMin, which returns the smallest element in the data structure, all in O(1) worst-case time.

就是利用兩個棧，一個存輸入序列，一個存至輸入序列為止時的最小值。

編程實現
----
```C++
#include <iostream>
#include <stack>

template<typename T>
class MinStack {
public:
    MinStack() :
        values(std::stack<T>()), minimums(std::stack<T>()) {
    }

    void push(T value) {
        values.push(value);
        if (!minimums.empty() && minimums.top() < value) {
            minimums.push(minimums.top());
        } else {
            minimums.push(value);
        }
    }

    T pop() {
        if (values.empty()) {
            return T(); // throw exception
        }
        T value = values.top();
        values.pop();
        minimums.pop();
        return value;
    }

    T findMin() {
        if (values.empty()) {
            return T(); // throw exception
        }
        return values.top();
    }

    size_t size() {
        return values.size();
    }

private:
    std::stack<T> values;
    std::stack<T> minimums;
};

//////////////////////////////////////////////////////////////////////////////
// test below
//

#include <random>
#include <ctime>

enum OperationType {
    PUSH,      // 0
    POP,       // 1
    FIND_MIN,  // 2
    TYPE_COUNT // 3
};

enum {
    TEST_SIZE = 8,
    MAX_NUM = 100,
};

int main() {
    srand((unsigned) time(0));

    MinStack<int> minStack;

    int operation, num;
    for (int i = 0; i < (TEST_SIZE * TYPE_COUNT) << 1; ++i) {
        operation = rand() % TYPE_COUNT;
        if (operation == PUSH) {
            num = rand() % MAX_NUM;
            minStack.push(num);
            printf("push %d\n", num);
        } else if (minStack.size() > 0) {
            if (operation == POP) {
                printf("pop %d\n", minStack.pop());
            } else {
                printf("min so far %d\n", minStack.findMin());
            }
        }
    }

    return 0;
}
```

