沒啥好說的，直接貼代碼。

*TODO: 以後可以實現一個基於鏈表的*

```C++
#include <functional>
#include <iostream>
#include <iterator>

#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
#  define LOG_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define LOG_DEBUG(fmt, ...)  do {} while (0)
#endif

namespace stack {

template<typename T> class array_stack {
public:
    array_stack(unsigned capacity = DEFAULT_CAPACITY) :
        __capacity(capacity),
        __size(0),
        __arr(new T[__capacity]) {
    }

    ~array_stack() {
        if(__arr) {
            delete[] __arr;
            __arr = NULL;
        }
        __size = 0;
    }

    void push(const T& elem) {
        if (__size == __capacity) {
            __resize();
        }
        __arr[__size++] = elem;
    }

    void pop() {
        if (__size == 0) {
            throw std::out_of_range("empty stack");
        }
        --__size;
    }

    T top() {
        if (__size == 0) {
            throw std::out_of_range("empty stack");
        }
        return __arr[__size - 1];
    }

    bool empty() {
        return __size == 0;
    }

private:
    void __resize() {
        LOG_DEBUG("resize array_stack from %d to %d", __capacity, __capacity << 1);
        __capacity <<= 1;
        int* new_arr = new int[__capacity];
        memcpy(new_arr, __arr, __size * sizeof(T));
        delete __arr;
        __arr = new_arr;
    }

private:
    static const unsigned DEFAULT_CAPACITY = 16;

private:
    unsigned __capacity;
    unsigned __size;
    T*       __arr;
};


} // end of namespace stack

#include <random>
#include <ctime>
#include <stack>

enum {
    TEST_SIZE = 23,
    MAX_NUM = 97
};

int main() {
    std::stack<int> stdstack;
    stack::array_stack<int> arrstack;

    srand((unsigned) time(0));

    for (int i = 0, num; i < TEST_SIZE; ++i) {
        num = rand() % MAX_NUM;
        stdstack.push(num);
        arrstack.push(num);
    }

    std::cout << "std stack: ";
    while (!stdstack.empty()) {
        std::cout << stdstack.top() << ' ';
        stdstack.pop();
    }
    std::cout << std::endl;

    std::cout << "arr stack: ";
    while (!arrstack.empty()) {
        std::cout << arrstack.top() << ' ';
        arrstack.pop();
    }
    std::cout << std::endl;

    return 0;
}
```
