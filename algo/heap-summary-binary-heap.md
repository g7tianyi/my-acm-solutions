堆小結之：二叉堆
====

二叉堆簡單強悍，是我最喜歡的數據結構之一。二叉堆形式上是數組（所以簡單），本質上是完全二叉樹（所以優雅），按照數據的排列方式可以分為兩種：

- 最大堆：父結點的鍵值總是大於或等於任何一個子節點的鍵值
- 最小堆：父結點的鍵值總是小於或等於任何一個子節點的鍵值

既然是完全二叉樹，又存放在數組里，節點的父子關係就很有規律了，假設第一個元素在數組中的索引為0的話，則父節點和子節點的位置關係如下：

- 索引為i的左孩子的索引是(2*i+1)
- 索引為i的左孩子的索引是(2*i+2)
- 索引為i的父結點的索引是floor((i-1)/2)

乘除2看著就爽，因為位運算可以發揮作用。

二叉堆的理解還是馬叔叔的圖最好，以插入為例：

![enter image description here](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/binary-heap-insertion.png)

這個過程封裝成```__percolate_up```，刪除時的過程基本相似，封裝成了```__percolate_down```。

```C++
#include <functional>
#include <iostream>
#include <iterator>

namespace heap {

template<typename T, typename Compare = std::less<T> >
class binary_heap {
public:
    binary_heap(int capacity) :
        __compare(Compare()),
        __capacity(capacity),
        __size(0),
        __arr(new T[capacity]) {}

    ~binary_heap() {
        __capacity = 0;
        __size = 0;
        delete[] __arr;
    }

    void push(const T value) {
        if (__size == __capacity) {
            // resize later
            return;
        }
        __arr[__size] = value;
        __percolate_up(__size);
        __size++;
    }

    void pop() {
        if (empty()) {
            // throw std::
            return;
        }
        __arr[0] = __arr[--__size];
        __percolate_down(0);
    }

    T top() {
        if (empty()) {
            throw std::out_of_range("empty heap");
        }
        return __arr[0];
    }

    bool empty() { return __size == 0; }
    int  size() { return __size; }
    void clear() { __size = 0; }

    T& operator[](int index) {
        if (index < 0 || index >= __size) {
            throw std::out_of_range("index out of heap range");
        }
        return *(__arr + index);
    }

private:
    void __percolate_down(int hole) {
        int next = (hole << 1) + 1;
        T temp = __arr[hole];
        while (next < __size) {
            if (next + 1 < __size // don't cross the border boundary
                    && __compare(__arr[next], __arr[next + 1])) {
                // think in terms of "__arr[next] < __arr[next + 1]"
                ++next;
            }
            if (__compare(temp, __arr[next])) {
                __arr[hole] = __arr[next];
                hole = next;
                next = (next << 1) + 1;
            } else {
                break;
            }
        }
        __arr[hole] = temp;
    }

    void __percolate_up(int hole) {
        T temp = __arr[hole];
        int prev = (hole - 1) >> 1; // parent
        while (hole) {
            if (__compare(temp, __arr[prev])) {
                // think in terms of "temp < __arr[prev]"
                break;
            } else {
                __arr[hole] = __arr[prev];
                hole = prev;
                prev = (prev - 1) >> 1;
            }
        }
        __arr[hole] = temp;
    }

private:
    Compare __compare;
    int __capacity;
    int __size;
    T*  __arr;
};

template<typename T, typename Compare = std::less<T> >
std::ostream& operator<<(std::ostream& os, binary_heap<T, Compare>& heap) {
    for (int i = 0; i < heap.size(); ++i) {
        os << heap[i] << ' ';
    }
    return os;
}

} // end of namespace heap

#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

enum {
    MAX_NUM = 97, HEAP_SIZE = 23
};

template<typename T, typename Compare = std::less<T> >
void test_heap(heap::binary_heap<T, Compare>& myheap) {
    for (int i = 0, num; i < HEAP_SIZE; ++i) {
        num = rand() % MAX_NUM;
        std::cout << num << ' ';
        myheap.push(num);
    }
    std::cout << std::endl;
    std::cout << myheap << std::endl;
    while (!myheap.empty()) {
        std::cout << "popped " << myheap.top() << ": ";
        myheap.pop();
        std::cout << myheap << std::endl;
    }
}

int main() {
    srand((unsigned) time(0));

    heap::binary_heap<int> maxheap(HEAP_SIZE);
    test_heap(maxheap);

    heap::binary_heap<int, std::greater<int> > minheap(HEAP_SIZE);
    test_heap(minheap);

    return 0;
}
```
