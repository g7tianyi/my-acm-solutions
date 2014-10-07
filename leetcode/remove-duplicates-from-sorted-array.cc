#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class Solution {
public:
    int removeDuplicates(int array[], int size) {
        if (size <= 1) {
            return size;
        }

        int pos = 1, last = 1, prev = array[0];
        bool flag = false;
        while (pos < size) {
            if (array[pos] != prev) {
                prev = array[pos];
                if (flag) {
                    swap(array[last], array[pos]);
                }
                ++last;
            } else {
                flag = true;
            }
            ++pos;
        }
        return last;
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
int TEST_SIZE[] = { 1, 12, 31, 14, 28, 0 };
int array[30];
void setUpTest(int size) {
    srand((unsigned) time(0));
    int i = 0, num, odds;
    for (; i < size;) {
        num = std::abs(rand() % 100);
        array[i++] = num;
        odds = rand() % 3;
        while (odds) {
            array[i++] = num;
            --odds;
        }
    }
    std::sort(array, array + size);
}
}

int main() {
    int test = sizeof(stest::TEST_SIZE) / sizeof(int);
    for (int i = 0; i < test; ++i) {
        int len = stest::TEST_SIZE[i];
        stest::setUpTest(len);
        std::cout << "Before: ";
        std::copy(stest::array, stest::array + len,
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        len = solution.removeDuplicates(stest::array, len);
        std::cout << "After : ";
        std::copy(stest::array, stest::array + len,
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    int arr1[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int len = sizeof(arr1) / sizeof(int);
    std::cout << "Before: ";
    std::copy(arr1, arr1 + len, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    len = solution.removeDuplicates(arr1, len);
    std::cout << "After : ";
    std::copy(arr1, arr1 + len, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}


