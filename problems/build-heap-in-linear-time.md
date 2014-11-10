線性時間內建堆
====

By [Mark Allen Weiss](http://users.cis.fiu.edu/~weiss/)

> Write a program to take N elements and do the following:

> a. Insert them into a heap one by one.

> b. Build a heap in linear time.

第一問在[這裡](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/heap-summary-binary-heap.md)。第二問其實CLRS裡面也有，所以不多說，關鍵是證明O(n)的複雜度。

令堆所對應的完全二叉樹的高度為h，節點的個數為n，現假定完全二叉樹為滿二叉樹：即n = 2^(h - 1)，有2^(h-2)個結點向下訪問一次，2^(h-3)個結點向下訪問2次，...1個結點向下訪問h次，然後就是一個求和公式了。

```C++
#include <functional>
#include <iterator>
#include <iostream>

template<typename RandomIterator,
         typename Compare = std::greater<typename RandomIterator::value_type> >
void linear_heapify(RandomIterator first, RandomIterator last,
        Compare compare = Compare()) {
    typedef typename RandomIterator::value_type      value_type;
    typedef typename RandomIterator::difference_type diff_type;

    diff_type  diff = last - first;
    for (diff_type hole = (diff - 1) >> 1; hole >= 0; --hole) {
        value_type temp = *(first + hole);
        diff_type  pare = hole, curr = (hole << 1) + 1;
        while (curr < diff) {
            if (curr < diff - 1 && compare(*(first + curr), *(first + curr + 1))) {
                ++curr;
            }
            if (compare(*(first + curr), temp)) {
                break;
            }
            *(first + pare) = *(first + curr);
            pare = curr;
            curr = (curr << 1) + 1;
        }
        *(first + pare) = temp;
    }
}

#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

enum {
    HEAP_SIZE = 23,
    MAX_NUM = 97
};

int main() {
    srand((unsigned) time(0));
    std::vector<int> vec;
    for (int i = 0; i < HEAP_SIZE; ++i) {
        vec.push_back(rand() % MAX_NUM);
    }

    std::cout << "original sequence: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    linear_heapify(vec.begin(), vec.end());
    std::cout << "heapfied sequence: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
------------------------------------------------------------------------------------
original sequence: 36 14 5 78 76 56 81 7 51 35 64 76 50 29 55 21 17 31 59 91 4 23 27 
heapfied sequence: 4 7 5 17 14 50 29 21 31 35 23 76 56 81 55 36 78 51 59 91 76 64 27 

```
