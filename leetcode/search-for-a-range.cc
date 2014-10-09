#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    vector<int> searchRange(int array[], int size, int key) {
        vector<int> V(2, -1);
        if (size <= 0) {
            return V;
        }

        int first = 0, last = size - 1, mid;
        bool found = false;
        while (first <= last) {
            mid = mean(first, last);
            if (array[mid] == key) {
                found = true;
                break;
            } else if (array[mid] < key) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }

        if (found) {
            first = mid;
            while (first > 0 && array[first - 1] == key) {
                --first;
            }
            last = mid;
            while (last < size - 1 && array[last + 1] == key) {
                ++last;
            }
            V[0] = first;
            V[1] = last;
        }

        return V;
    }
private:
    inline int mean(int small, int large) {
        return small + ((large - small) >> 1);
    }
};

Solution sol;

void test(int array[], int size, int key) {
    std::cout << "searching " << key << " in ";
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    vector<int> V = sol.searchRange(array, size, key);
    std::cout << V[0] << ", " << V[1] << std::endl;
}

int main() {
    int arr0[] = { 5, 7, 7, 8, 8, 10 };
    int arr1[] = { 1, 5, 7, 8, 9, 12, 16 };
    int arr2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    test(arr0, sizeof(arr0) / sizeof(int), 8);
    test(arr0, sizeof(arr0) / sizeof(int), 6);
    test(arr1, sizeof(arr1) / sizeof(int), 8);
    test(arr1, sizeof(arr1) / sizeof(int), 6);
    test(arr2, sizeof(arr2) / sizeof(int), 1);
    test(arr2, sizeof(arr2) / sizeof(int), 2);

    return 0;
}

