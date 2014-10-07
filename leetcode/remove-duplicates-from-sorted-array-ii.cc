#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    int removeDuplicates(int array[], int size) {
        if (size <= 0) {
            return size;
        }
        int dup = -1, prev = array[0], count = 1, removed = 0;
        for (int i = 1; i < size; ++i) {
            if (array[i] == prev) {
                ++count;
            } else {
                removed += (count > 2 ? count - 2 : 0);
                prev = array[i];
                count = 1;
            }

            if (count <= 2 && dup != -1) {
                array[dup++] = array[i];
            }
            if (count > 2 && dup == -1) {
                dup = i;
            }
        }
        removed += (count > 2 ? count - 2 : 0);
        return size - removed;
    }
};

static Solution solution;

namespace stest {

enum {
    MAX_RAND = 100, MAX_NUM = 128, MAX_DUP = 5
};
static int array[MAX_NUM];

static void mockRandomData(int size) {
    srand((unsigned) time(0));
    if (size > MAX_NUM || size < 0) {
        size = MAX_NUM;
    }
    int count = 0;
    while (count < size) {
        int times = 1 + std::abs(rand()) % MAX_DUP;
        if (times > size - count) {
            times = size - count;
        }
        int num = std::abs(rand()) % MAX_RAND;
        while (times--) {
            array[count++] = num;
        }
    }
    std::sort(array, array + size);
}
static void mockEdgeCase(int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i + 1;
    }
}
static void print(int size) {
    std::copy(array, array + size, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
static void setUpRandomTest(int size) {
    mockRandomData(size);
}
static void setUpEdgeTest(int size) {
    mockEdgeCase(size);
}
static void runTest(int size) {
    std::cout << ">>> the original array: ", print(size);
    int len = solution.removeDuplicates(array, size);
    std::cout << ">>> new size: " << len << std::endl;
    std::cout << ">>> duplicates removed: ", print(len);
}

static void testRandomData(int size) {
    setUpEdgeTest(size);
    runTest(size);
}
static void testEdgeData(int size) {
    setUpRandomTest(size);
    runTest(size);
    std::cout << std::endl;
}

void run() {
    testRandomData(1), testEdgeData(1);
    testRandomData(17), testEdgeData(17);
    testRandomData(43), testEdgeData(43);
    testRandomData(100), testEdgeData(100);
    testRandomData(MAX_NUM), testEdgeData(MAX_NUM);
}

}

int main() {
    stest::run();
    return 0;
}

