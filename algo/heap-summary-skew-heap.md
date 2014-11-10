堆小結之：斜堆
====
引用一段話，當然還是來自[Mark叔叔](http://users.cis.fiu.edu/~weiss/)，信息量很大：

> A **skew heap** is a self-adjusting version of a leftist heap that is incredibly simple to implement. **The relationship of skew heaps to leftist heaps is analogous to the relation between splay trees and AVL trees.** **Skew heaps are binary trees with heap order, but there is no structural constraint on these trees.** Unlike leftist heaps, no information is maintained about the null path length of any node. The right path of a skew heap can be arbitrarily long at any time, so the worst-case running time of all operations is O(N). However, as with splay trees, it can be shown (see Chapter 11) that for any M consecutive operations, the total worst-case running time is O(MlogN). Thus, skew heaps have O(logN) amortized cost per operation.

##斜堆的合併操作

1. 如果一個空斜堆與一個非空斜堆合併，返回非空斜堆
2. 如果兩個斜堆都非空，那麼比較兩個根節點，取較小堆的根節點為新的根節點。將較小堆的根節點的右孩子和較大堆合併
3. 合併後，交換新堆根節點的左孩子和右孩子

![skew-heap-merge-1.png](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/skew-heap-1.png)

![skew-heap-merge-2.png](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/skew-heap-2.png)

##编程实现

斜堆与左式堆很像，实现也很像，斜堆还简单一些。

```C++
#include <functional>
#include <iostream>
#include <iterator>

namespace heap {

template<typename T>
struct skew_heap_node {
    T value;
    skew_heap_node<T> *left, *right;

    skew_heap_node() :
        value(T()), left(NULL), right(NULL) {
    }
    skew_heap_node(T _value) :
        value(_value), left(NULL), right(NULL) {
    }
};

template<typename T, typename Compare = std::greater<T> >
class skew_heap {
public:
    typedef skew_heap<T, Compare>  self_type;
    typedef skew_heap<T, Compare>* self_pointer;
    typedef skew_heap_node<T>      node_type;
    typedef skew_heap_node<T>*     node_pointer;

public:
    skew_heap() :
        __size(0), __root(NULL), __compare(Compare()) {
    }

    ~skew_heap() {
        clear();
    }

    node_pointer get_root() {
        return __root;
    }

    void merge(self_pointer other) {
        __root = __merge(__root, other->get_root());
    }

    T top() {
        if (empty()) {
            throw std::out_of_range("leftist heap is empty");
        }
        return __root->value;
    }

    void push(const T& value) {
        node_pointer node = new node_type(value);
        __root = __merge(__root, node);
        ++__size;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("leftist heap is empty");
        }
        node_pointer left = __root->left;
        node_pointer right = __root->right;
        __root = __merge(left, right);
        --__size;
    }

    int  size()  { return __size; }
    bool empty() { return __size == 0; }
    void clear() {
        __release(__root);
        __size = 0;
    }

private:
    void __swap(node_pointer& x, node_pointer& y) {
        node_pointer t = x;
        x = y;
        y = t;
    }
	
	/**
	 * For leftist heaps, we check to see whether the left
	 * and right children satisfy the leftist heap structure
	 * property and swap them if they do not.
	 * For skew heaps, the swap is unconditional; we always do
	 * it, with the one exception that the largest of all the
	 * nodes on the right paths does not have its children 
	 * swapped. This one exception is what happens in the
	 * natural recursive implementation, so it is not really
	 * a special case at all.
	 */
    node_pointer __merge(node_pointer x, node_pointer y) {
        if (x == NULL) {
            return y;
        }
        if (y == NULL) {
            return x;
        }

        if (__compare(x->value, y->value)) {
            // suppose the heap is a min-heap
            // hence x->value > y->value
            __swap(x, y);
        }

        node_pointer temp = __merge(x->right, y);
        x->right = x->left;
        x->left = temp;

        return x;
    }

    void __release(node_pointer x) {
        if (x == NULL) {
            return;
        }
        __release(x->left);
        __release(x->right);
        delete x;
    }

private:
    int          __size;
    node_pointer __root;
    Compare      __compare;
};

} // end of nammespace heap


// test below
#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

enum {
    MAX_NUM = 97, HEAP_SIZE = 23
};

template<typename T, typename Compare = std::less<T> >
void test_heap(heap::skew_heap<T, Compare>& myheap) {
    std::cout << "push ";
    for (int i = 0, num; i < HEAP_SIZE; ++i) {
        num = rand() % MAX_NUM;
        std::cout << num << ' ';
        myheap.push(num);
    }
    std::cout << std::endl;

    std::cout << "pop  ";
    while (!myheap.empty()) {
        std::cout <<  myheap.top() << ' ';
        myheap.pop();
    }
    std::cout << std::endl;
}

int main() {
    srand((unsigned) time(0));

    heap::skew_heap<int> maxheap;
    test_heap(maxheap);

    heap::skew_heap<int, std::less<int> > minheap;
    test_heap(minheap);

    return 0;
}
```
