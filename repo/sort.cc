#include <functional>
#include <iterator>

// various kind of sort algorithm
// 1) quick sort
// 2) shell sort
// 3) bubble sort
// 4) selection sort

namespace sort {

// swap two values
template<typename T>
void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

// split one sequence into two and return the partition address
template<typename RandomIterator, typename Compare>
RandomIterator __unguarded_partition(RandomIterator first, RandomIterator last,
        typename RandomIterator::value_type pivot, Compare compare) {
    for (;;) {
        for (; compare(*first, pivot); ++first)
            ;
        for (--last; compare(pivot, *last); --last)
            ;
        if (!(first < last))
            return first;
        swap(*first, *last);
        ++first;
    }
}

// quick sort
template<typename RandomIterator, typename Compare = std::less<typename RandomIterator::value_type> >
void quick_sort(RandomIterator first, RandomIterator last, Compare compare =
        Compare()) {
    if (last - first > 1) {
        typedef typename RandomIterator::value_type value_type;
        value_type pivot = *(first + ((last - first) >> 1));
        RandomIterator cut = __unguarded_partition(first, last, pivot, compare);
        quick_sort(first, cut, compare);
        quick_sort(cut, last, compare);
    }
}

// shell sort
template<typename RandomIterator, typename Compare>
inline void __shell_sort(RandomIterator first, RandomIterator last,
        typename RandomIterator::difference_type incre,
        typename RandomIterator::value_type value, Compare compare) {
    for (; first > last; first -= incre) {
        if (compare(value, *(first - incre))) {
            *first = *(first - incre); // looks like bubble sort
        } else {
            break;
        }
    }
    *first = value;
}

// for Hibbard sequence： 1, 3, 7, 15, 31, 63, 127,
// worst cast time complexity O(n^(3/2))
template<typename RandomIterator, typename Compare = std::less<typename RandomIterator::value_type> >
inline void shell_sort(RandomIterator first, RandomIterator last, Compare compare =
        Compare()) {
    if (last - first < 2) {
        return;
    }
    typedef typename RandomIterator::difference_type difference_type;
    difference_type incre = ((last - first) >> 1) - 1;
    for (; incre > 1; incre = (incre >> 1) - 1) {
        for (RandomIterator iter = first + (incre + 1); iter < last; ++iter) {
            __shell_sort(iter, first + incre, incre, *iter, compare);
        }
    }
    // the last incremental value must be 1
    for (RandomIterator iter = first + 1; iter < last; ++iter) {
        __shell_sort(iter, first, 1, *iter, compare);
    }
}

// bubble sort
template<typename RandomIterator, typename Compare = std::less<typename RandomIterator::value_type> >
void bubble_sort(RandomIterator first, RandomIterator last, Compare compare = Compare()) {
    if (first == last || first + 1 == last) {
        return;
    }
    for (bool bubbled = true; bubbled && first != last; --last) {
        bubbled = false;
        for (RandomIterator curr = first + 1; curr != last; ++curr) {
            RandomIterator prev = curr - 1;
            if (compare(*curr, *prev)) {
                swap(*curr, *prev);
                bubbled = true;
            }
        }
    }
}

// select the minimum/maximum (depends on compare) from [first, last)
template<typename ForwardIterator, typename Compare = std::less<typename ForwardIterator::value_type> >
ForwardIterator selection(ForwardIterator first, ForwardIterator last, Compare compare) {
    ForwardIterator next = first;
    for (++first; first != last; ++first) {
        if (compare(*first, *next)) {
            next = first;
        }
    }
    return next;
}

template<typename ForwardIterator, typename Compare = std::less<typename ForwardIterator::value_type> >
void selection_sort(ForwardIterator first, ForwardIterator last, Compare compare) {
    if (first == last || first + 1 == last) {
        return;
    }
    ForwardIterator curr, pos;
    for (curr = first; first != last; ++first, ++curr) {
        pos = __selection(first, last, compare);
        if (pos != curr) {
            swap(*curr, *pos);
        }
    }
}

void counting_sort(std::vector<int>& coll) {
    if (coll.empty() || coll.size() == 1) {
        return;
    }

    typedef std::vector<int>::size_type size_type;
    int max_value = *(coll.begin()), min_value = *(coll.begin());
    for (size_type i = 0; i < coll.size(); ++i) {
        if (max_value < coll[i]) {
            max_value = coll[i];
        }
        if (min_value > coll[i]) {
            min_value = coll[i];
        }
    }

    std::vector<int> bucket(max_value - min_value + 1, 0);
    for (size_type i = 0; i < coll.size(); ++i) {
        ++bucket[coll[i] - min_value];
    }
    for (size_type i = 0, j = 0; i < bucket.size(); ++i) {
        while (bucket[i]--) {
            coll[j++] = i + min_value;
        }
    }
}


} // end of namespace sort

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

namespace stest {

enum {
    MAX_NUM = 97, ARR_LEN = 23,
};

static std::vector<int> vec;
typedef std::vector<int>::iterator iterator;

template<typename ForwardIterator>
inline void print(ForwardIterator first, ForwardIterator last) {
    typedef typename ForwardIterator::value_type value_type;
    std::copy(first, last, std::ostream_iterator<value_type>(std::cout, " "));
    std::cout << std::endl;
}

template<typename Iterator, typename Compare = std::less<typename Iterator::value_type> >
void execute(void (*sort)(Iterator, Iterator, Compare), std::string type) {
    // prepare
    std::cout << "execute " << type << ": \n";
    vec.clear();
    for (int i = 0; i < ARR_LEN; ++i) {
        vec.push_back(rand() % MAX_NUM);
    }
    print(vec.begin(), vec.end());
    // run sort
    sort(vec.begin(), vec.end(), Compare());
    // show result
    print(vec.begin(), vec.end());
    std::cout << std::endl;
}

} // end of stest

int main() {

    srand((unsigned) time(0));

    stest::execute<stest::iterator>(sort::quick_sort,     "quick sort");
    stest::execute<stest::iterator>(sort::shell_sort,     "shell sort");
    stest::execute<stest::iterator>(sort::bubble_sort,    "bubble sort");
    stest::execute<stest::iterator>(sort::selection_sort, "selection sort");

    return 0;
}

