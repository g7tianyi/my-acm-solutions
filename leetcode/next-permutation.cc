#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    void nextPermutation(vector<int>& array) {
        int size = array.size();
        if (size <= 1) {
            return;
        }

        int curr = array[size - 1], prev = array[size - 2];
        int i = size - 3;
        while (i >= -1) {
            if (prev < curr) {
                break;
            }
            curr = prev;
            prev = array[i--];
        }

        if (i < -1) {
            // 9  8  7  7  6  5  4  3  1
            // =>
            // 1  3  4  5  6  7  7  8  9
            std::reverse(array.begin(), array.end());
        } else {
            // could try binary search here
            //        i        j     j
            //        |        |  => |
            // ... 9  8  4  7  6  6  5  3  1
            //           |  |
            //        prev  curr
            int j = i + 2;
            while (j + 1 < size && array[j + 1] > prev) {
                ++j;
            }
            //        i i+1          j
            //        |  |           |
            // ... 9  8  5  7  6  6  4  3  1
            std::swap(array[j], array[i + 1]);
            std::reverse(array.begin() + i + 2, array.end());
        }
    }
};

Solution solu;

#include <ctime>
#include <unistd.h>

vector<int> V;
inline void printArray() {
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    V.clear();
    V.push_back(1), V.push_back(3), V.push_back(2);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    V.clear();
    V.push_back(3), V.push_back(2), V.push_back(1);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    V.clear();
    V.push_back(1), V.push_back(1), V.push_back(5);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    V.clear();
    V.push_back(6), V.push_back(7), V.push_back(5);
    V.push_back(4), V.push_back(3), V.push_back(2);
    V.push_back(1);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    V.clear();
    V.push_back(9), V.push_back(8), V.push_back(4);
    V.push_back(7), V.push_back(6), V.push_back(6);
    V.push_back(5), V.push_back(3), V.push_back(1);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    V.clear();
    V.push_back(9), V.push_back(8), V.push_back(7);
    V.push_back(7), V.push_back(6), V.push_back(5);
    V.push_back(4), V.push_back(3), V.push_back(2);
    printArray();
    solu.nextPermutation(V);
    printArray();
    std::cout << std::endl;

    srand((unsigned) time(0));
    for (int i = 0; i < 10; ++i) {
        V.clear();
        int size = 5 + std::abs(rand()) % 20;
        for (int j = 0; j < size; ++j) {
            V.push_back(std::abs(rand()) % 20);
        }
        printArray();
        solu.nextPermutation(V);
        printArray();
        std::cout << std::endl;
        usleep(1000 * 1000);
    }


    return 0;
}

