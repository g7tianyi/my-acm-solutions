#include <iostream>

class Solution {
public:
    int removeElement(int array[], int size, int key) {
        int last = size - 1, curr;
        while (last >= 0 && array[last] == key) {
            --last;
        }
        curr = last;
        while (curr >= 0) {
            if (array[curr] == key) {
                swap(array[curr], array[last]);
                --last;
            }
            --curr;
        }
        return last + 1;
    }
private:
    inline void swap(int& a, int& b) {
        int t = a;
        a = b, b = t;
    }
};
static Solution solution;

inline void print(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = { 1, 4, 5, 6, 4, 3, 4, 1, 11, 6, 19, 4 };
    int len = solution.removeElement(arr1, sizeof(arr1) / sizeof(int), 4);
    printf("new arr1: "), print(arr1, len);
    printf("ori arr1: "), print(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
    len = solution.removeElement(arr2, sizeof(arr2) / sizeof(int), 4);
    printf("new arr2: "), print(arr2, len);
    printf("ori arr2: "), print(arr2, sizeof(arr2) / sizeof(int));

    int arr3[] = { 4, 4, 5, 4, 4, 4, 5, 4, 4, 4, 4, 4, 4 };
    len = solution.removeElement(arr3, sizeof(arr3) / sizeof(int), 4);
    printf("new arr3: "), print(arr3, len);
    printf("ori arr3: "), print(arr3, sizeof(arr3) / sizeof(int));

    int arr4[] = { };
    len = solution.removeElement(arr4, sizeof(arr4) / sizeof(int), 4);
    printf("new arr4: "), print(arr4, len);
    printf("ori arr4: "), print(arr4, sizeof(arr4) / sizeof(int));

    int arr5[] = { 1, 14, 5, 6, 24, 3, 44, 1, 11, 6, 19, 34 };
    len = solution.removeElement(arr5, sizeof(arr5) / sizeof(int), 4);
    printf("new arr5: "), print(arr5, len);
    printf("ori arr5: "), print(arr5, sizeof(arr5) / sizeof(int));

    return 0;
}

