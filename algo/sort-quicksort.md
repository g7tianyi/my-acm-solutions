快速排序的實現
====
```C++
/**
 * QuickSort
 *
 * Divide:
 *     Partition (rearrange) the array A[p..r] into two (possibly empty)
 *     subarrays A[p..q-1] and A[q+1..r] such that each element of A[p..q-1]
 *     is less than or equal to A[q] which is, in turn, less than or equal to
 *     each elemen of A[q+1..r]. Compute the index q as part of this partitioning
 *     procedure.
 * Conquer:
 *     Sort the two subarrays A[p..q-1] and A[q+1..r] by recursive calls to quicksort.
 *
 * QUICKSORT(A, p r)
 *   if p < r
 *     q = PARTITION(A, p, r)
 *   QUICKSORT(A, p, q - 1)
 *   QUICKSORT(A, p + 1, q)
 *
 * PARTITION(A, p, r)
 *   x = A[r]
 *   i = p-1
 *   for j from i to r-1
 *     if A[j] <= x
 *         i＝ i + 1
 *         swap(A[i], A[j)
 *   swap(A[i+1], A[r])
 *   return i + 1
 *
 */

// simplified version
/**
 * idea, based on divide-and-conquer method
 * 1) selection. select a number as the pivot
 * 2) partition. put all numbers larger than pivot to its right, and smaller to the left
 * 3) recursion. repeat step 1) and 2) for the left and right range
 */
void quick_sort(int array[], int first, int last) {
    if (first < last) {
        int i = first, j = last, pivot = array[first];
        while (i < j) {
            //        i                             j
            //        |                             |
            // array: 42 74 90 37 59 39 47 90 53 18 66
            // pivot: 42
            while (i < j && array[j] >= pivot) {
                j--;
            }
            if (i < j) {
                array[i++] = array[j];
            }
            //           i                       j
            //           |                       |
            // array: 18 74 90 37 59 39 47 90 53 18 66
            // pivot: 42
            while (i < j && array[i] < pivot) {
                i++;
            }
            if (i < j) {
                array[j--] = array[i];
            }
            //           i                    j
            //           |                    |
            // array: 18 74 90 37 59 39 47 90 53 74 66
            // pivot: 42

            // i < j, keep looping
        }
        array[i] = pivot;
        quick_sort(array, first, i - 1);
        quick_sort(array, i + 1, last);
    }
}

// sophisticated version below

template<typename T>
inline void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template<typename T, typename Compare>
inline const T& median(const T& a, const T& b, const T& c, Compare compare) {
    if (compare(a, b)) {
        if (compare(b, c)) {
            return b;
        } else if (compare(a, c)) {
            return c;
        } else {
            return a;
        }
    } else if (compare(a, c)) {
        return a;
    } else if (compare(b, c)) {
        return c;
    } else {
        return b;
    }
}

/**
 * PARTITION(A, p, r)
 *   x = A[r]
 *   i = p-1
 *   for j from i to r-1
 *     if A[j] <= x
 *         i＝ i + 1
 *         swap(A[i], A[j)
 *   swap(A[i+1], A[r])
 *   return i + 1
 */
template<typename RandomIterator, typename T, typename Compare>
RandomIterator unguarded_partition(RandomIterator first, RandomIterator last,
        T& pivot, Compare compare) {
    for (;;) {
        for (; compare(*first, pivot); ++first)
            ;
        for (--last; compare(pivot, *last); --last)
            ;
        if (!(first < last)) {
            return first;
        }
        swap(*first, *last);
        ++first;
    }
}

// the maximum depth of recursion if possible
inline int log(int n) {
    int k;
    for (k = 0; n > 1; n >>= 1) {
        ++k;
    }
    return k;
}

// an auxilary function for sort
template<typename RandomIterator, typename Compare>
void introsort_loop(RandomIterator first, RandomIterator last, int depth_limit,
        Compare compare) {
    while (last - first > 16) {
        if (0 == depth_limit) {
            partial_sort(first, last, last, compare);
            return;
        }
        --depth_limit;
        RandomIterator cut = unguarded_partition(first, last,
                median(*first, *(first + ((last - first) >> 1)), *(last - 1),
                        compare), compare);
        introsort_loop(cut, last, depth_limit, compare);
        last = cut;
    }
}

// quick sort -- SGI STL version
template<typename RandomIterator, typename Compare>
inline void sort(RandomIterator first, RandomIterator last, Compare compare) {
    if (last - first > 16) {
        introsort_loop(first, last, log(static_cast<int>(last - first)) << 1,
                compare);
    }
    final_insertion_sort(first, last, compare);
}
```
