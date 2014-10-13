#include <algorithm>
#include <iostream>

class Solution {
public:
    int firstMissingPositive(int array[], int size) {
        int i = 0;
        while (i < size) {
            if (array[i] != i + 1 && array[i] > 0 && array[i] <= size
                    && array[array[i] - 1] != array[i]) {
                std::swap(array[i], array[array[i] - 1]);
            } else {
                ++i;
            }
        }
        for (i = 0; i < size; ++i) {
            if (array[i] != (i + 1)) {
                return i + 1;
            }
        }
        return size + 1;
    }
};

Solution solu;

int main() {
    int arr1[] = { 1, 2, 0 };
    std::cout << solu.firstMissingPositive(arr1, 3) << std::endl;
    int arr2[] = { 3, 4, -1, 1 };
    std::cout << solu.firstMissingPositive(arr2, 4) << std::endl;
    return 0;
}

