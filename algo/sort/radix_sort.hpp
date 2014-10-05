#include <ctime>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <algorithm>

#define STUDY_MODE

// non-portable implementation for LSD radix sort, for type int, 64 bit system
template<typename ForwardIterator>
void radix_sort(ForwardIterator first, ForwardIterator last) {
    // R: radix, K: k base, M: mask, B: ? bit system
    const unsigned R = 8, K = 1 << R, M = K - 1, B = 64;
    std::deque<int> Q[K];
    // sort by every consecutive R bits
    for (unsigned i = 0; i < B; i += R) {
        ForwardIterator iter;
        for (iter = first; iter != last; ++iter) {
            Q[(*iter >> i) & M].push_back(*iter);
        }

#ifdef STUDY_MODE
        std::cout << ">>> sort by the " << i << "-th " << R << " bits:\n";
        for (unsigned j = 0; j < K; ++j) {
            if (!Q[j].empty()) {
                std::copy(Q[j].begin(), Q[j].end(),
                        std::ostream_iterator<int>(std::cout, " "));
                std::cout << "\n";
            }
        }
#endif
        iter = first;
        for (unsigned j = 0; j < K; ++j) {
            while (!Q[j].empty()) {
                *iter++ = Q[j].front();
                Q[j].pop_front();
            }
        }
    }
}

int main() {
    const int MAX = 100;
    std::srand(std::time(0)); // use current time as seed for random generator
    std::deque<int> deq;
    for (int i = 0; i < 20; ++i) {
        deq.push_back(std::rand() % MAX);
    }
    std::cout << "Before sort: ";
    std::copy(deq.begin(), deq.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    radix_sort(deq.begin(), deq.end());
    std::cout << "After sort:  ";
    std::copy(deq.begin(), deq.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    return 0;
}

