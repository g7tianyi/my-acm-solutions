#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    bool canJump(int jump[], int size) {
        if (size <= 0) {
            return false;
        }
        int min = size - 1;
        for (int i = size - 2; i >= 0; --i) {
            if (i + jump[i] >= min) {
                min = i;
            }
        }
        return min == 0;
    }
};

Solution sol;

int arr0[] = { 2, 3, 1, 1, 4 };
int arr1[] = { 3, 2, 1, 0, 4 };

void test(int jump[], int size) {
    if (sol.canJump(jump, size)) {
        std::cout << "can jump to the rear." << std::endl;
    } else {
        std::cout << "can't jump to the rear." << std::endl;
    }
}

int main() {
    test(arr0, sizeof(arr0) / sizeof(int));
    test(arr1, sizeof(arr1) / sizeof(int));
    return 0;
}

