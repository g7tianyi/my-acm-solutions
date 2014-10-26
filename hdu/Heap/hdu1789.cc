/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1789
 * Greedy algorithm. Min-Heap
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

static int const MAX_WORK = 1001;
struct Homework {
    int deadline, value;
};
Homework work[MAX_WORK];

inline bool workComp(const Homework& lhs, const Homework& rhs) {
    return lhs.deadline < rhs.deadline;
}

template<typename T, typename Compare> class Heap {
public:
    Heap() : compare(Compare()) {
        std::make_heap(container.begin(), container.end(), compare);
    }

    const T& top() const {
        return *(container.begin());
    }

    void push(const T& item) {
        container.push_back(item);
        std::push_heap(container.begin(), container.end(), compare);
    }

    T pop() {
        std::pop_heap(container.begin(), container.end(), compare);
        T popped = container.back();
        container.pop_back();
        return popped;
    }

    bool empty() const {
        return container.empty();
    }

    size_t size() const {
        return container.size();
    }

    void clear() {
        container.clear();
    }

private:
    Compare compare;
    std::vector<T> container;
};

int main() {
    int T, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &work[i].deadline);
        }
        int total = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &work[i].value);
            total += work[i].value;
        }
        std::sort(work, work + N, workComp);

        Heap<int, std::greater<int> > heap;
        for (int i = 0, days = 0; i < N; ++i) {
            if (work[i].deadline > days) {
                heap.push(work[i].value);
                ++days;
            } else if (work[i].deadline == days) {
                if (heap.top() < work[i].value) {
                    heap.pop(), heap.push(work[i].value);
                }
            }
        }
        int left = 0;
        while (!heap.empty()) {
            left += heap.pop();
        }
        printf("%d\n", total - left);
    }

    return 0;
}

