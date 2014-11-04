Summary of Binary Search
=========
0) Interesting~ binary search optimization in ACM
----
> [poj 3273](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/DataStructure/poj3273.cc)

> [poj 3258](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/DataStructure/poj3258.cc)

1) The basic problem
----
1. Open or closed range?
I intend to use the closed range, i.e., [first, last], when there's only one element in the checking range, we have first == last, thus the looping condition is first <= last.

2. How to get mid?
use (first + last) / 2 could have many side effects, e.g., division is not very efficient, addition could be overflow, so my preference is always use first + ((last - first) >> 1)

3. How to update first/last?
If the target lies in the left, we update last to be (mid - 1), if right, we update the first to be (mid + 1)

```C++
template<typename T>
int binarySearch(T array[], int size, T target) {
    int first = 0, last = size - 1;
    while (first <= last) {
        int mid = first + ((last - first) >> 1);
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    return -1;
}
```
2) Find the index the target appeared the first time
----
```C++
/**
 * in the range [first, last],
 * 1) if array[mid] >= target, we drop the range [mid + 1, last], because elements in
 *    [mid + 1, last] either larger than the target or equals to the target but doesn't
 *    appear the first time
 * 2) if array[mid] < target, then they all can not be the answers, we update the first
 *    to be mid + 1.
 * But we can not use first <= last as the loop condition, since if there's only one
 * element in the checking range and we go into the case 1), we have,
 *   first == last,
 *   mid = first + ((last - first) >> 1) = first.
 * infinit loop comes by.
 *
 * when we finally finished the loop, we would have first > last, so
 */
template<typename T>
int lower_bound(T array[], int size, T target) {
    int first = 0, last = size - 1;
    while (first < last) {
        int mid = first + ((last - first) >> 1);
        if (array[mid] >= target) {
            last = mid;
        } else {
            first = mid + 1;
        }
    }
    return array[first] == target ? first : -1;
}
```
> Problem: https://github.com/g7tianyi/my-acm-solutions/blob/master/leetcode/search-for-a-range.cc

3) Find the index the target appeared the last time
----
```C++
/**
 * no more explanation about searching the last place
 */
template<typename T>
int upper_bound(T array[], int size, T target) {
    int first = 0, last = size - 1;
    while (first < last) {
        int mid = first + ((last - first) >> 1);
        if (array[mid] <= target) {
            first = mid;
        } else {
            last = mid - 1;
        }
    }
    return array[first] == target ? first : -1;
}
```
> Problem: https://github.com/g7tianyi/my-acm-solutions/blob/master/leetcode/search-for-a-range.cc

4) Find the pos for insertion
----
```C++
template<typename T>
int insertion_pos(T array[], int size, T target) {
    int first = 0, last = size - 1, mid;
    while (first <= last) {
        mid = first + ((last - first) >> 1);
        if (array[mid] == target) {
            return mid;
        }
        if (mid > first && array[mid] > target && array[mid - 1] < target) {
            return mid;
        }

        if (array[mid] > target) {
            last = mid - 1;
        } else {
            first = mid + 1;
        }
    }
    // WATCH OUT:
    // return first to get the index of the one who's LARGER than the target
    // return last to get the index of the one who's SMALLER than the target
    return first;
}

#include <cstdio>

enum ELEM_COUNT {
    ODD_ELEM = 7, EVEN_ELEM = 8
};
int arr1[ODD_ELEM] = { 1, 3, 4, 6, 7, 8, 10 };
int arr2[EVEN_ELEM] = { 1, 4, 5, 6, 7, 11, 12, 18 };

int main() {
    printf("Test 1: %d\n", insertion_pos(arr1, ODD_ELEM, 0));
    printf("Test 2: %d\n", insertion_pos(arr1, ODD_ELEM, 7));
    printf("Test 3: %d\n", insertion_pos(arr1, ODD_ELEM, 5));
    printf("Test 4: %d\n", insertion_pos(arr1, ODD_ELEM, 11));

    printf("Test 5: %d\n", insertion_pos(arr2, EVEN_ELEM, 0));
    printf("Test 6: %d\n", insertion_pos(arr2, EVEN_ELEM, 8));
    printf("Test 7: %d\n", insertion_pos(arr2, EVEN_ELEM, 6));
    printf("Test 8: %d\n", insertion_pos(arr2, EVEN_ELEM, 21));
}
```
> Problem: https://github.com/g7tianyi/my-acm-solutions/blob/master/leetcode/search-insert-position.cc

5) Find missing element in [0, n]
----
```C++
// the given array contains all elements in [0, n] but one
// the algorithm missing_elem use binary search to find it
template<typename T>
int missing_elem(T array[], int size) {
    int first = 0, last = size - 1, mid;
    while (first < last) { // WATCH OUT: can not be '<='
        mid = first + ((last - first) >> 1);
        if (array[mid] == mid) { // the range [0, mid] are all good
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first; // here first equals to last actually
}

#include <cstdio>

enum ELEM_COUNT {
    ODD_ELEM = 9, EVEN_ELEM = 8
};
int arr1[ODD_ELEM] = { 0, 1, 2, 3, 4, 5, 7, 8, 9 };
int arr2[EVEN_ELEM] = { 0, 1, 2, 3, 5, 6, 7, 8 };

int main() {
    printf("%d\n", missing_elem(arr1, ODD_ELEM));
    printf("%d\n", missing_elem(arr2, EVEN_ELEM));
    return 0;
}
```
6) Search rotated array (no duplicates)
----
```C++
template<typename T>
int search_rotated(T array[], int size, T target) {
    int first = 0, last = size - 1, mid;
    // *) if target == array[mid], return mid
    // *) case (#1) if array[mid] > array[first], range [first, mid] is sorted,
    //    then check if key is in this range, update first/last
    // *) case (#2) if array[mid] < array[last], range [mid, last] is sorted,
    //    then check if key is in this range, update first/last
    while (first <= last) {
        mid = first + ((last - first) >> 1);
        if (target == array[mid]) {
            return mid;
        }

        if (array[mid] > array[first]) {
            // case (#1)
            // check the former range
            // first          mid          last
            //  |              |            |
            //  8 10 14 16 17 18 20 21 24 1 2 3 4 5 6 7
            if (target >= array[first] && target <= array[mid - 1]) {
                // then key must be in the sorted range [first, mid - 1]
                last = mid - 1;
            } else {
                first = mid + 1;
            }
        } else {
            // case (#2)
            // check the latter range
            //                     first   mid   last
            //                      |       |     |
            //  8 10 14 16 17 18 20 21 24 1 2 3 4 5 6 7
            if (target <= array[last] && target >= array[mid + 1]) {
                // then key must be in the sorted range [mid + 1, last]
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }
    }
    return -1;
}
```
7) Search rotated array (has duplicates)
---
```C++
template<typename T>
int search_rotated(T array[], int size, const T& target) {
    if (size == 0) {
        return false;
    }

    int first = 0, last = size - 1, mid;
    while (first <= last) {
        mid = first + ((last - first) >> 1);
        if (array[mid] == target) {
            return true;
        }

        if (array[first] < array[mid]) {
            /**
             * range [first, mid] is sorted, check if target
             * is in this range and update first/last
             */
            if (target >= array[first] && target <= array[mid - 1]) {
                last = mid - 1;
            } else {
                first = mid + 1;
            }
        } else if (array[first] > array[mid]) {
            /**
             * range [mid, last] is sorted, check if target
             * is in this range and update first/last
             */
            if (array[mid] < target && array[last] >= target) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        } else {
            /**
             * array[first] equals array[mid]
             * no clue that which part can be droped
             * case #1:
             *   5 5 5 5 5 5 5 1 2 3 4
             *   |         |         |
             * first      mid       last
             * case #2:
             *   5 5 6 7 8 5 5 5 5 5 5
             *   |         |         |
             * first      mid      last
             * So the algo may degenerate to O(N)
             */
            ++first;
        }
    }
    return false;
}
```

