排序小結
====

- 快速排序
- Shell排序
- 冒泡排序
- 選擇排序

##快速排序

對於一個無需序列而言，當我們需要把它變成一個升序序列時，可以把它一分為二，使左邊的子序列都小於或等於某個值，右邊的子序列都大於等於某個值，左右子序列繼續這種劃分，直到整個序列有序為止。這是最原始的快速排序設計思想，它是分治算法的應用。

現在的問題是，拿什麼作為基準把一個序列劃分成兩個子序列呢？弄不好一邊只有一個元素，另一邊則為其餘所有元素，這是最糟糕的情況，完全退化成了直接插入排序，複雜度為O(N^2)。

選取支點常見的方案有三種:

- 第一種情況是使用待排序序列的第一個元素或最後一個元素作為支點。採用這種方案的人非常樂觀，以為最壞情況很難遇上，然而事情很多時候總是事與願違，當一個待排序序列已經有序時就會遭遇最差情況
- 第二種方案是三點取中，以待排序序列中第一個元素，最中間那個元素和最後一個元素三者大小居中的那個作為支點，這就大大降低了遭遇最差情況的可能性，而且三點取中的代價很低
- 第三種選取支點的方案的原理非常簡單，隨機選擇，就是CLRS上討論的，不過軟件生成隨機數并不是一件容易的事情，隨機數的質量對算法的效率會有不好表達清楚的影響

```C++
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
template<typename RandomIterator, typename Compare = std::less<
        typename RandomIterator::value_type> >
inline void quick_sort(RandomIterator first, RandomIterator last, Compare compare =
        Compare()) {
    if (last - first > 1) {
        typedef typename RandomIterator::value_type value_type;
        value_type pivot = *(first + ((last - first) >> 1));
        RandomIterator cut = __unguarded_partition(first, last, pivot, compare);
        quick_sort(first, cut, compare);
        quick_sort(cut, last, compare);
    }
}
```

##希爾排序

希爾排序的原理是首先比較遠距離的元素，然後遞減比較距離，**最終比較相鄰元素**（這個是關鍵）。由於採用這種比較方式來排序，希爾排序有時候也被稱為遞減增量排序。增量序列的不同將直接影響希爾排序的速度，因此，不方便給出希爾排序理論上的時間複雜度。Hibbard采用的增量序列为：1, 3, 7, ..., 2^K– 1，(K = 1, 2, ...)，這個也好編程，但複雜度不怎麼好分析，號稱是O(N^(3/2))。

```C++
// shell sort
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
template<typename RandomIterator, typename Compare = std::less<
         typename RandomIterator::value_type> >
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
```

##冒泡排序

對於序列中每一個元素，當後面的元素比當前元素小時，交換之，直到整個序列無元素交換為止，則整個序列成為一個有序序列。

冒泡排序的時間複雜度為O(N^2)，空間複雜度為O(1)，當原始序列已經有序，則冒泡排序的時間複雜度為O(N)。當待排序序列基本有序時，使用冒泡排序速度往往比較快。

```C++
template<typename RandomIterator, typename Compare = std::less<
        typename RandomIterator::value_type> >
void bubble_sort(RandomIterator first, RandomIterator last, Compare compare = Compare()) {
    if (first == last || first + 1 == last) {
        return;
    }
    // every time the biggest one bubbled to last, so we decrement last
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
```

##選擇排序

假設一個待排序的序列中有N個元素，從這N個元素中選出一個最小(大)的元素放在第0個元素的位置，再從餘下的N-1元素中選出一個次小(大)的元素放在第1個元素的位置，繼續這個過程，經過N-1次選擇和交換，整個序列成為一個升(降)序序列，這就是選擇排序的排序過程。

無論最好還是最壞情況，選擇排序的時間複雜度始終為O(N^2)，空間複雜度為O(1)。

```C++
// select the minimum/maximum (depends on compare) from [first, last)
template<typename ForwardIterator, typename Compare = std::less<
        typename ForwardIterator::value_type> >
ForwardIterator selection(ForwardIterator first, ForwardIterator last, Compare compare) {
    ForwardIterator next = first;
    for (++first; first != last; ++first) {
        if (compare(*first, *next)) {
            next = first;
        }
    }
    return next;
}

template<typename ForwardIterator, typename Compare>
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
```

*未完待續*
