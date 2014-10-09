#include <iostream>

class Solution {
public:
    bool isPalindrome(int num) {
        if (num < 0) {
            return false;
        }
        int tmp = num, high = 0, low = 10;
        while (tmp) {
            tmp /= 10;
            if (high) {
                high *= 10;
            } else {
                high = 1;
            }
        }

        while (num) {
            if (num / high != num % low) {
                return false;
            }
            num %= high;
            num /= low;
            high /= 100;
        }

        return true;
    }
};

Solution sol;

inline void test(int num) {
    std::cout << num << " is "
            << (sol.isPalindrome(num) ? "palindrome" : "not palindrome")
            << std::endl;
}

int main() {

    int dataSet[] = { -19, -121, 6, 13, 77, 121, 123, 2222, 2232, 19891, 198891,
            2147447412, 214787412, 2147483647, };

    for (int i = 0; i < sizeof(dataSet) / sizeof(int); ++i) {
        test(dataSet[i]);
    }

    return 0;
}

