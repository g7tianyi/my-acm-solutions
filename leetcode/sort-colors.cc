#include <algorithm>
#include <iostream>
#include <ctime>

class Solution {
public:
    void sortColors(int array[], int size) {
        int last = size - 1;
        for (int i = 2; i > 0; --i) {
            int j = 0;
            while (j <= last) {
                if (array[j] == i) {
                    while (last > j && array[last] == i) {
                        --last;
                    }
                    if (j < last) {
                        swap(array[j], array[last]);
                    }
                    --last;
                }
                ++j;
            }
        }
    }
private:
    inline void swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }
};
static Solution solution;

namespace stest {

int array[128];

void test(int size) {
    srand((unsigned) time(0));
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 3;
    }
    std::cout << "original array: ";
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    solution.sortColors(array, size);
    std::cout << "sorted array  : ";
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n" << std::endl;
}

}

int main() {
    using namespace stest;
    for (int i = 1; i <= 128; ++i) {
        test(i);
    }
    return 0;
}

