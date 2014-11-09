长度为3的不连续有序子序列问题
====

給定一個長度為```n```的數列，求三元組(A<sub>i</sub>, A<sub>j</sub>, A<sub>k</sub>)的個數，滿足

- i < j < k
- A<sub>i</sub> < A<sub>j</sub>, A<sub>k</sub> < A<sub>j</sub>

##解法

> [kenny的解法](https://github.com/philoprove/revolutionary-road/blob/master/mind-garden/ijk.md)

> [kevin的解法](https://github.com/chen8913w/Algo/blob/master/src/org/practice/middle/large/MiddleLargeOptimize.java)

我的第一個思路基於動態規劃。```prev[i]```記錄前面比```arr[i]```小的，```next[i]```記錄後面比```arr[i]```小的，從下面的實現看，這個複雜度是```O(n^2)```，kevin的代碼還把```prev```和```next```的空間開銷優化了，很好~

另外其實可以用樹的思路來思考。模擬輸的插入過程，對於序列```1 2 3 4 1```，設想各個元素依次插入一颗二叉排序树，一旦往右走，意味著當前待插入節點的```prev```值就加```1```。那麼怎麼得到```next```值呢？其實逆序再插入一顆新的樹就可以了。對於隨機數據，可以逼近```O(nlogn)```的复杂度，最壞情況是```O(n^2)```。

還有誰可以想到線性複雜度的算法嗎？

```C++
// dp
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>

void test_dp(int arr[], int len) {
    int prev[len], next[len];
    memset(prev, 0, sizeof(prev));
    memset(next, 0, sizeof(next));

    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) {
                ++prev[i];
            }
        }
    }

    for (int i = len - 2; i >= 0; --i) {
        for (int j = len - 1; j > i; --j) {
            if (arr[j] < arr[i]) {
                ++next[i];
            }
        }
    }

    int result = 0;
    for (int i = 0; i < len; ++i) {
        result += (prev[i] * next[i]);
    }
    printf("%d\n", result);
}

enum {
    MAX_ARR_LEN = 100000,
    MAX_ARR_NUM = 1000,
    TEST_CASE = 5
};

int main() {

    int arr0[5] = { 1, 2, 3, 4, 1 };
    std::copy(arr0, arr0 + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    test_dp(arr0, 5);

    srand((unsigned) time(0));

    int len;
    int arr[MAX_ARR_LEN];

    for (int i = 0; i < TEST_CASE; ++i) {
        len = 1 + rand() % MAX_ARR_LEN;
        for (int j = 0; j < len; ++j) {
            arr[j] = 1 + rand() % MAX_ARR_NUM;
        }
        std::copy(arr, arr + len, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        test_dp(arr, len);
    }

    return 0;
}
```
