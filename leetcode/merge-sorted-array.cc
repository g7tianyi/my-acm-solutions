#include <algorithm>
#include <iostream>

class Solution {
public:
    void merge(int arr1[], int size1, int arr2[], int size2) {
        // shift arr1 to the rear of arr1
        int i = size1 - 1, j = i + size2;
        while (i >= 0) {
            arr1[j--] = arr1[i--];
        }

        int pos = 0;
        i = j + 1, j = 0;
        while (i < size1 + size2 && j < size2) {
            if (arr1[i] < arr2[j]) {
                arr1[pos++] = arr1[i++];
            } else {
                arr1[pos++] = arr2[j++];
            }
        }
        while (j != size2) {
            arr1[pos++] = arr2[j++];
        }
    }
};
static Solution solution;

namespace stest {
int arr11[10] = { 7, 8, 13, 22, 30 };
int arr12[4]  = { 6, 7, 8, 11 };

int arr21[10] = { 7, 8, 13, 22, 30 };
int arr22[4]  = { 2, 3, 4, 5 };

int arr31[10] = { 2, 3, 4, 5, 30 };
int arr32[4]  = { 7, 8, 13, 22 };

int arr41[10] = { 2, 4, 4, 4, 30 };
int arr42[4]  = { 7, 8, 13, 22 };

int arr51[10] = { 2 };
int arr52[4]  = { 7, 8, 13, 22 };

int arr61[10] = { 11 };
int arr62[4]  = { 7, 8, 13, 22 };

int arr71[10] = { 7, 8, 13, 22 };
int arr72[4]  = { 18 };

void test(int arr1[], int size1, int arr2[], int size2) {
    std::cout << "array 1: ";
    std::copy(arr1, arr1 + size1, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "array 2: ";
    std::copy(arr2, arr2 + size2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "merged : ";
    solution.merge(arr1, size1, arr2, size2);
    std::copy(arr1, arr1 + size1 + size2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << std::endl;
}

}

int main() {
    using namespace stest;
    test(arr11, 5, arr12, 4);
    test(arr21, 5, arr22, 4);
    test(arr31, 5, arr32, 4);
    test(arr41, 5, arr42, 4);
    test(arr51, 1, arr52, 4);
    test(arr61, 1, arr62, 4);
    test(arr71, 4, arr72, 1);
    return 0;
}

