#include <vector>
#include <algorithm>
#include <functional>

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

