#include <iostream>

class Solution {
public:
    bool search(int array[], int size, int key) {
        if (size == 0) {
            return false;
        }

        int first = 0, last = size - 1, mid;
        while (first <= last) {
            mid = first + ((last - first) >> 1);
            if (array[mid] == key) {
                return true;
            }

            if (array[first] < array[mid]) {
                /**
                 * range [first, mid] is sorted, check if key
                 * is in this range and update first/last
                 */
                if (key >= array[first] && key <= array[mid - 1]) {
                    last = mid - 1;
                } else {
                    first = mid + 1;
                }
            } else if (array[first] > array[mid]) {
                /**
                 * range [mid, last] is sorted, check if key
                 * is in this range and update first/last
                 */
                if (array[mid] < key && array[last] >= key) {
                    first = mid + 1;
                } else {
                    last = mid - 1;
                }
            } else {
                /**
                 * array[first] equals array[mid]
                 *   5 5 5 5 5 5 5 1 2 3 4
                 *   |         |         |
                 * first      mid       last
                 * no clue that which part can be droped
                 * So the algo may degenerate to O(N)
                 */
                ++first;
            }
        }
        return false;
    }
};

Solution solu;

int array1[10] = { 4, 4, 4, 5, 6, 7, 0, 1, 2, 4 };
int array2[10] = { 8, 9, 12, 14, 1, 2, 4, 5, 6, 7 };
int array3[10] = { 2, 3, 5, 7, 8, 10, 11, 13, 15, 23 };

int main() {
    std::cout << solu.search(array1, 10, 4) << std::endl;
    std::cout << solu.search(array1, 10, 6) << std::endl;
    std::cout << solu.search(array1, 10, 7) << std::endl;
    std::cout << solu.search(array1, 10, 0) << std::endl;
    std::cout << std::endl;

    std::cout << solu.search(array2, 10, 4) << std::endl;
    std::cout << solu.search(array2, 10, 9) << std::endl;
    std::cout << solu.search(array2, 10, 1) << std::endl;
    std::cout << solu.search(array2, 10, 14) << std::endl;
    std::cout << std::endl;

    std::cout << solu.search(array3, 10, 4) << std::endl;
    std::cout << solu.search(array3, 10, 9) << std::endl;
    std::cout << solu.search(array3, 10, 1) << std::endl;
    std::cout << solu.search(array3, 10, 15) << std::endl;
    std::cout << std::endl;

    return 0;
}

