堆小結之：左式堆
====

基本的[二叉堆](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/heap-summary-binary-heap.md)簡單優雅好理解，不過涉及到合併操作時效率不太令人滿意，二叉堆要完成**合併**，其實就是把一個堆中的元素一一```pop```出來在```push```到另一個堆裡面去。

左式堆、二項堆以及斐波那契堆都是表現很優秀的支持合併操作的堆，看我能不能一一總結。在我個人的實踐經驗里，還沒有遇到明確需要高效率的堆合併操作的場合，只能以後補充了。

下面是左式堆的實例：

![leftist heap](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/leftist-heap.png)

根據[Mark叔叔](http://users.cis.fiu.edu/~weiss/)，左式堆的節點除了和二叉對的節點一樣具有左右子樹指針外，還有兩個屬性：

- **鍵值**
- **零距離**，這玩意叫**Null Path Length (NPL)**，表示從一個節點到最近一個沒有兩個兒子的節點的路徑長度。葉節點的NPL為0，NULL節點的NPL為-1。

左式堆有以下幾個基本性質：

1. 節點的鍵值*小於等於*（根據 Predicate(C++) / Comparator(Java) 而定）它的左右子節點的鍵值
2. 節點的左孩子的NPL >= 右孩子的NPL。所以傾向左偏斜嘛。
3. 節點的NPL = 它的右孩子的NPL + 1。依定義而來的嘛。

##合併

合併操作是左式堆的重點。合併兩個左式堆的基本過程如下：

1. 如果一個空左式堆與一個非空左式堆合併，返回非空左式堆
2. 如果兩個左式堆都非空，那麼比較兩個根節點，取較小堆的根節點為新的根節點，將較小堆的根節點的右孩子和較大堆進行合併
3. 如果新堆的右孩子的NPL > 左孩子的NPL，則交換左右孩子
4. 設置新堆的根節點的NPL = 右子堆NPL + 1

下面的代碼里有個圖示範了這個過程。

##編程實現
```C++
#include <functional>
#include <iostream>
#include <iterator>

namespace heap {

template<typename T>
struct leftist_heap_node {
    T value;
    int __npl; // null path length
    leftist_heap_node<T> *left, *right;

    leftist_heap_node() :
        value(T()), __npl(0), left(NULL), right(NULL) {
    }
    leftist_heap_node(T _value) :
        value(_value), __npl(0), left(NULL), right(NULL) {
    }
};

template<typename T, typename Compare = std::greater<T> >
class leftist_heap {
public:
    typedef leftist_heap<T, Compare>  self_type;
    typedef leftist_heap<T, Compare>* self_pointer;
    typedef leftist_heap_node<T>      node_type;
    typedef leftist_heap_node<T>*     node_pointer;

public:
    leftist_heap() :
        __size(0), __root(NULL), __compare(Compare()) {
    }

    ~leftist_heap() {
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
        delete __root;
        --__size;
        __root = __merge(left, right);
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

    // ---------------------------------------|
    //          x        |         y          |
    // ---------------------------------------|
    //          3        |         6          |
    //       /     \     |       /   \        |
    //     10       8    |     12     7       |
    //    /  \     /     |    /  \   /  \     |
    //  21   14  17      |  18   24 37  18    |
    //          /        |       /            |
    //         23        |     33             |
    // ---------------------------------------|
    //          6        |         8          |
    //        /   \      |        /           |
    //      12     7     |       17           |
    //     /  \   /  \   |      /             |
    //    18  24 37  18  |     23             |
    //   /               |                    |
    //  33               |                    |
    // ---------------------------------------|
    //        7          |         8          |
    //      /   \        |        /           |
    //     37   18       |      17            |
    //                   |     /              |
    //                   |    23              |
    // ---------------------------------------|
    //         8         |        18          |
    //        /          |                    |
    //      17           |                    |
    //     /             |                    |
    //   23              |                    |
    // ---------------------------------------|
    //                   8                    |
    //                 /   \                  |
    //               17     18                |
    //              /                         |
    //            23                          |
    // ---------------------------------------|
    // finally                                |
    //                   6                    |
    //                /     \                 |
    //              12       7                |
    //             /  \     /  \              |
    //           18   24   8   37             |
    //               /   /   \                |
    //             33  17    18               |
    //                /                       |
    //              23                        |
    // ---------------------------------------|
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

        x->right = __merge(x->right, y);

        if (x->left == NULL
                || x->left->__npl < x->right->__npl) {
            __swap(x->left, x->right);
        }

        if (x->left == NULL || x->right == NULL) {
            x->__npl = 0;
        } else {
            x->__npl = std::min(x->left->__npl, x->right->__npl) + 1;
        }

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

// -------------------------------------------------------------------
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
void test_heap(heap::leftist_heap<T, Compare>& myheap) {
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

    heap::leftist_heap<int> maxheap;
    test_heap(maxheap);

    heap::leftist_heap<int, std::less<int> > minheap;
    test_heap(minheap);

    return 0;
}

----------------------------------------------------------------------
Sample output:
push 24 43 20 27 37 92 59 65 63 64 87 26 36 39 77 26 73 74 82 52 62 3 25 
pop  3 20 24 25 26 26 27 36 37 39 43 52 59 62 63 64 65 73 74 77 82 87 92 
push 50 85 74 12 53 43 15 14 92 12 9 72 72 78 39 38 86 48 21 26 3 86 85 
pop  92 86 86 85 85 78 74 72 72 53 50 48 43 39 38 26 21 15 14 12 12 9 3 
```
