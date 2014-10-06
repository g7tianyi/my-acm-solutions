#include <iostream>
#include <limits>

class Solution {
public:
    typedef long long LONG;
public:
    int reverse(int num) {
        LONG res = 0, tmp = static_cast<LONG>(num);
        bool positive = true;
        if (tmp < 0) {
            positive = false, tmp *= -1;
        }
        while (tmp) {
            res = res * FACTOR + tmp % FACTOR;
            tmp /= 10;
        }
        if (res > std::numeric_limits<int>::max()) {
            return positive ?
                    std::numeric_limits<int>::max() :
                    std::numeric_limits<int>::min();
        }
        return positive ? res : res * -1;
    }
private:
    static int const FACTOR = 10;
};

Solution solution;

int main() {

    int arr[] = { 0, 123, -123, 9, -9, 1000, -1000, 1000000003, -1000000003,
            2147483647, -2147483648 };

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
        printf("Testing %d => %d\n", arr[i], solution.reverse(arr[i]));
    }

    return 0;
}

