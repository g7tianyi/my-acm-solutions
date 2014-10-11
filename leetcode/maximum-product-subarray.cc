#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int maxProduct(int array[], int size) {
        int allmax = array[0], curmax = array[0], curmin = array[0];
        int prodmax, prodmin;
        for (int i = 1; i < size; ++i) {
            prodmax = curmax * array[i], prodmin = curmin * array[i];
            curmin = std::min(array[i], std::min(prodmax, prodmin));
            curmax = std::max(array[i], std::max(prodmax, prodmin));
            allmax = std::max(allmax, curmax);
        }
        return allmax;
    }
};

Solution sol;

#include <unistd.h>
#include <ctime>
int array[50];
void test(int size) {
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    for (int i = 0, j; i < size; ++i) {
        j = rand() % 3;
        array[i] = rand() % 10;
        array[i] *= (j == 0 ? -1 : 1);
    }
    std::cout << "testing ";
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " => ";
    std::cout << sol.maxProduct(array, size) << std::endl;
}

int main() {
    memset(array, 0, sizeof(array));
    std::cout << "testing ";
    std::copy(array, array + 10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " => ";
    std::cout << sol.maxProduct(array, 10) << std::endl;

    for (int i = 1; i < 10; ++i) {
        array[i] = -i;
    }
    std::cout << "testing ";
    std::copy(array, array + 10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " => ";
    std::cout << sol.maxProduct(array, 10) << std::endl;

    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < 5; ++j) {
            test(i * j);
            usleep(1000 * 1000);
        }
    }

    memset(array, 0, sizeof(array));
    std::cout << "testing ";
    std::copy(array, array + 10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " => ";
    std::cout << sol.maxProduct(array, 10) << std::endl;

    for (int i = 1; i < 10; ++i) {
        array[i] = -i;
    }
    std::cout << "testing ";
    std::copy(array, array + 10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " => ";
    std::cout << sol.maxProduct(array, 10) << std::endl;

    return 0;
}

