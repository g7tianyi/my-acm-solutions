#include <iostream>

class Solution {
public:
    int search(int array[], int size, int key) {
        int first = 0;
        int last = size - 1;
        while (first <= last) {
            int mid = mean(first, last);
            if (key == array[mid]) {
                return mid;
            }

            // 1) if key == array[mid], return
            // 2) if array[mid] > array[first], range [first, mid] is sorted,
            //    then check if key (#1) is in this range, update first/last
            // 3) if array[mid] < array[last], range [mid, last] is sorted,
            //    then check if key (#2) is in this range, update first/last

            if (array[mid] > array[first]) {
                // check the former range (#1)
                // first          mid          last
                //  |              |            |
                //  8 10 14 16 17 18 20 21 24 1 2 3 4 5 6 7
                if (key >= array[first] && key <= array[mid - 1]) {
                    // then key must be in the sorted range
                    last = mid - 1;
                } else {
                    first = mid + 1;
                }
            } else {
                // check the latter range (#2)
                //                     first   mid   last
                //                      |       |     |
                //  8 10 14 16 17 18 20 21 24 1 2 3 4 5 6 7
                if (key <= array[last] && key >= array[mid + 1]) {
                    // then key must be in the sorted range
                    first = mid + 1;
                } else {
                    last = mid - 1;
                }
            }
        }
        return -1;
    }
private:
    inline int mean(int small, int large) {
        return small + ((large - small) >> 1);
    }
};

Solution solu;

int main() {
    int array[] = { 4, 5, 6, 7, 0, 1, 2 };
    int size = sizeof(array) / sizeof(int);
    for (int i = 0; i < size; ++i) {
        std::cout << "searching " << array[i] << ": " << solu.search(array, size, array[i])
                << std::endl;
    }
    std::cout << "searching " << 12 << ": " << solu.search(array, size, 12) << std::endl;

    return 0;
}

