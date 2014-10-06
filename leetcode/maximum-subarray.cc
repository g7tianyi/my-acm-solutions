#include <iostream>
#include <algorithm>

class Solution {
public:
    int maxSubArray(int array[], int size) {
        if (size <= 0) {
            return 0;
        }
        int allmax = array[0], curmax = array[0];
        for (int i = 1; i < size; ++i) {
            if (curmax > 0) {
                curmax += array[i];
            } else {
                curmax = array[i];
            }
            allmax = max(allmax, curmax);
        }
        return allmax;
    }
private:
    inline int max(int a, int b) {
        return a > b ? a : b;
    }
};

Solution solution;

int main() {
    int array1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    printf("Testing 1: %d\n",
            solution.maxSubArray(array1, sizeof(array1) / sizeof(int)));

    int array2[] = { 1 };
    printf("Testing 2: %d\n",
            solution.maxSubArray(array2, sizeof(array2) / sizeof(int)));

    int array3[] = { -2, -1, -3, -4, -10, -2, -8, -5, -67 };
    printf("Testing 1: %d\n",
            solution.maxSubArray(array3, sizeof(array3) / sizeof(int)));

    int array4[] = { -2, -1, -3, -4, -10, -2, -8, 0, -67 };
    printf("Testing 1: %d\n",
            solution.maxSubArray(array4, sizeof(array4) / sizeof(int)));

    int array5[] = { 2, 1, 3, 4, 0, 2, 8, 5, 67 };
    printf("Testing 5: %d\n",
            solution.maxSubArray(array5, sizeof(array5) / sizeof(int)));

    return 0;
}

