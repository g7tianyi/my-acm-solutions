#include <iostream>
#include <algorithm>

class Solution {
public:
    int searchInsert(int array[], int size, int key) {
        int first = 0, last = size - 1, middle;
        while (first <= last) {
            middle = mean(first, last);
            if (array[middle] == key) {
                return middle;
            }
            if (middle > first && array[middle] > key
                    && array[middle - 1] < key) {
                return middle;
            }
            if (array[middle] > key) {
                last = middle - 1;
            } else {
                first = middle + 1;
            }
        }
        return first;
    }
private:
    inline int mean(int small, int large) {
        return small + ((large - small) >> 1);
    }
};
Solution solution;

int main() {
    int array[] = { 1, 3, 5, 6 };
    printf("Test 1: %d\n",
            solution.searchInsert(array, sizeof(array) / sizeof(int), 5));
    printf("Test 2: %d\n",
            solution.searchInsert(array, sizeof(array) / sizeof(int), 2));
    printf("Test 3: %d\n",
            solution.searchInsert(array, sizeof(array) / sizeof(int), 7));
    printf("Test 4: %d\n",
            solution.searchInsert(array, sizeof(array) / sizeof(int), 0));

    return 0;
}

