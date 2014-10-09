#include <iostream>

inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}

#include <vector>
class Solution {
public:
    int trap(int array[], int size) {
        if (size <= 0) {
            return 0;
        }
        std::vector<int> V;
        int curmax = array[0];
        V.push_back(curmax);
        for (int i = 1; i < size; ++i) {
            if (curmax < array[i]) {
                curmax = array[i];
            }
            V.push_back(curmax);
        }

        curmax = array[size - 1];
        for (int i = size - 1; i > 0; --i) {
            if (V[i] == array[i]) {
                break;
            }
            if (curmax < array[i]) {
                curmax = array[i];
            }
            V[i] = curmax;
        }

        int result = 0;
        for (int i = 0; i < size; ++i) {
            result += (V[i] - array[i]);
        }
        return result;
    }
};

Solution sol;

int arr1[] = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
int arr2[] = { 10, 0, 0, 0, 0, 0, 0, 9 };
int arr3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int arr4[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
int arr5[] = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1, 3, 2, 1, 2, 1 };
int arr6[] = { 4, 2, 0, 3, 2, 5 };
int arr7[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 9 };

void test(int array[], int size) {
    std::cout << "Test array with size " << size << ": ";
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::cout << sol.trap(array, size) << std::endl;
}

int const MAX_SIZE = 10000;
int array[MAX_SIZE];

#include <ctime> // don't write code so arbitrarily in real life
void randomTest(int size) {
    srand((unsigned) time(0));
    size = min(size, MAX_SIZE);
    for (int i = 0; i < size; ++i) {
        array[i] = std::abs(rand()) % 100;
    }
    test(array, size);
}

int main() {
    test(arr1, sizeof(arr1) / sizeof(int));
    test(arr2, sizeof(arr2) / sizeof(int));
    test(arr3, sizeof(arr3) / sizeof(int));
    test(arr4, sizeof(arr4) / sizeof(int));
    test(arr5, sizeof(arr5) / sizeof(int));
    test(arr6, sizeof(arr6) / sizeof(int));
    test(arr7, sizeof(arr7) / sizeof(int));

    randomTest(7);
    randomTest(8);
    randomTest(9);

    randomTest(20);
    randomTest(21);
    randomTest(22);

    randomTest(MAX_SIZE - 2);
    randomTest(MAX_SIZE - 1);
    randomTest(MAX_SIZE);

    return 0;
}

