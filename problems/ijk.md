长度为3的不连续有序子序列问题
====

注意这里的有序，指结果中的序列符合要求的顺序，不一定是从小到大 给你一个序列A，比如 1 2 3 4 1 求三个元素 Ai Aj Ak 满足 Ai < Aj Ak < Aj, i < j < k 算一下一共有多少种取法 1 2 3 4 1 一共6种取法

##解法

> [DFS思路 by kenny](https://github.com/philoprove/revolutionary-road/blob/master/mind-garden/ijk.md)
> [枚举思路 by kevin](https://github.com/chen8913w/Algo/blob/master/src/org/practice/middle/large/MiddleLargeNaive.java)

我的思路一个是DP，prev记录前面比arr[i]小的，next[i]记录后面比arr[i]小的，从下面的实现可以看出，这个复杂度是O(N^2)。

另外其实可以用树的思路来思考。模拟树的插入过程，对于序列```1 2 3 4 1```，依次插入一颗二叉排序树，一旦当前节点往右走，意味着当前节点的prev值就加1。那么怎么得到next值呢？其实逆序再插入一颗新的数就可以了，考虑树要是平衡书话，其实可以达到O(nlogn)的复杂度。


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
