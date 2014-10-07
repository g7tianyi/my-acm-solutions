#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int maxContainer = 0, size = height.size();
        int first = 0, last = size - 1;
        while (first < last) {
            maxContainer = max(maxContainer,
                    (last - first) * min(height[first], height[last]));
            if (height[first] < height[last]) {
                first++;
            } else {
                last--;
            }
        }
        return maxContainer;
    }
private:
    inline int min(int a, int b) {
        return a < b ? a : b;
    }
    inline int max(int a, int b) {
        return a > b ? a : b;
    }
};
static Solution solution;

namespace stest {

static const int MAX_RAND = 49;

static vector<int> mockData(int size) {
    vector<int> V;
    srand((unsigned) time(0));
    for (int i = 0; i < size; ++i) {
        V.push_back(1 + std::abs(rand()) % MAX_RAND);
    }
    return V;
}

static void print(vector<int>& vec) {
    std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

static void test(int size) {
    vector<int> V = mockData(size);
    std::cout << ">>> height: ";
    print(V);
    std::cout << "Max Area => " << solution.maxArea(V) << "\n" << std::endl;
}

void run() {
    test(1);
    test(5);
    test(7);
    test(10);
    test(100);
}

}

int main() {
    stest::run();
    return 0;
}

