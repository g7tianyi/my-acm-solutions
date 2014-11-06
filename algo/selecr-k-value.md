K值問題小結
====

> 給定一個長度為N的無序數組，找出其中第K大的數。

- 直接對數組排序，然後直接就挑出來了，複雜度(NlogN)
- 選擇排序的思路，掃描數組K次，複雜度O(N*K)
- 建最大/小堆，堆大小為K，複雜度O(NlogK)
- 借助快速排序partition過程的思路，複雜度可以達到O(N)，具體做法就是從數組arr中隨機找出一個元素pivot，把數組分為兩部分P1和P2。 P1中的元素大於等於X，P2中元素小於X。這時有兩種情況： 
  * P1中元素的個數小於K，則P2中的第K - len(P1)個元素即為第K大數
  * P1中元素的個數大於等於K，則返回P1中的第K大數
- 桶排序的的思路，或者說哈希。要求數據均勻分佈在一個不要太大的區間里（不然空間開銷太大），掃描數組將數據dispatch到各個桶裡面去，或者記錄每個數字出現的次數，然後順序掃描桶/哈希表
- 平衡二叉樹的思路，見[這裡](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/tree-essential-5.md)，這個也是O(NlogN)的，不過樹建好之後，後面就都是O(logN)了，一些場合下還是很值得考慮的

##基於快排思路的代碼實現
```C++
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>

template<typename T>
inline void swap(T& a, T& b) {
    T t = a; a = b; b = t;
}

template<typename T>
T nth_elem(T arr[], int first, int last, int n) {
	if (n > last - first) {
		throw std::out_of_range("index out of range");
	}
    int i = first, j = last;
    int elem = arr[first + ((last - first) >> 1)];
    while (i <= j) {
        while (arr[i] < elem)
            ++i;
        while (arr[j] > elem)
            --j;
        if (i <= j) {
            swap(arr[i], arr[j]);
            ++i; --j;
        }
    }

    if (first < j && n <= j) {
        return nth_elem(arr, first, j, n);
    }
    if (i < last && n >= i) {
        return nth_elem(arr, i, last, n);
    }
    return arr[n];
}

// test below
enum {
    ARR_LEN = 23,
    MAX_NUM = 97
};

int arr1[ARR_LEN], arr2[ARR_LEN];

int main() {

    srand((unsigned) time(0));

    for (int i = 0, num; i < ARR_LEN; ++i) {
        num = rand() % MAX_NUM;
        arr1[i] = arr2[i] = num;
    }

    std::sort(arr2, arr2 + ARR_LEN);

    for (int i = 0, num; i < ARR_LEN; ++i) {
        num = nth_elem(arr1, 0, ARR_LEN-1, i);
        std::cout << i + 1 << " element:\t"
                << num << " VS " << arr2[i]
                << std::endl;
    }

    return 0;
}
```
