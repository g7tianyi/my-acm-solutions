#include <iostream>

/**
 * the basic problem
 *
 * 1) open or closed range.
 *    i tend to use closed range, i.e., [first, last], when there's only one element in
 *    the checking range, we have first == last, thus the looping condition is
 *    first <= last.
 * 2) how to get mid.
 *    use (first + last) / 2 could have many side effects, e.g., division is not very
 *    efficient, addition could be overflow, so my preference is always use
 *    first + ((last - first) >> 1)
 * 3) how to update first/last
 *    if the target lies in the left, we update last to be (mid - 1), if right, we update
 *    the first to be (mid + 1).
 */
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

/**
 * find the index an element appeared the first time
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


