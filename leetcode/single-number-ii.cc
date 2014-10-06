#include <iostream>
#include <algorithm>

class Solution {
public:
    int singleNumber(int array[], int size) {
        // one, two, three
        // the mask code indicating times of 1s for the i-th bits
        int one = 0, two = 0, three = 0;
        for (int i = 0; i < size; ++i) {
            two |= (one & array[i]);
            one ^= array[i];

            three = one & two;
            one &= ~three; // clear the third time appeared bits
            two &= ~three;
        }
        return one;
    }
};

Solution solution;

int main() {
    int array1[] = { 1, 3, 1, 4, 1, 8, 4, 3, 3, 4 };
    int array2[] = { 8 };
    printf("Testing 1: %d\n",
            solution.singleNumber(array1, sizeof(array1) / sizeof(int)));
    printf("Testing 2: %d\n",
            solution.singleNumber(array2, sizeof(array2) / sizeof(int)));
    return 0;
}

