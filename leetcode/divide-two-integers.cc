#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
using std::vector;

class Solution {
public:
    typedef unsigned long long ULONG;

    int divide(int dividend, int divisor) {
        if (divisor == 0) {
            throw "divisor can not be 0";
        }

        int sign = ((dividend > 0) ^ (divisor > 0)) ? -1 : 1;

        ULONG divd = static_cast<ULONG>(dividend);
        ULONG divs = static_cast<ULONG>(divisor);

        divd = dividend > 0 ? divd : -divd;
        divs = divisor > 0 ? divs : -divs;

        int result = 0;
        while (divd >= divs) {

            ULONG temp = static_cast<ULONG>(divs);
            int multiple = 0;
            while (temp <= divd) {
                ++multiple;
                temp <<= 1;
            }
            result += (1 << (multiple - 1));
            divd -= (divs << (multiple - 1));
        }

        return result * sign;
    }
};

Solution solu;

#include <ctime>
#include <unistd.h>
vector<vector<char> > matrix;

int main() {
    srand((unsigned) time(0));
    for (int i = 1; i <= 50; ++i) {
        int dividend = std::abs(rand()), divisor = std::abs(rand()) % 10000;
        int signs = std::abs(rand()) % 4;
        if (signs == 1) {
            dividend *= -1;
        } else if (signs == 2) {
            divisor *= -1;
        } else if (signs == 3) {
            dividend *= -1;
            divisor *= -1;
        }
        std::cout << dividend << " / " << divisor << " = " << solu.divide(dividend, divisor) << " | "
                << (dividend) / (divisor) << std::endl;
    }

#include <limits>

    int dividend = std::abs(rand());
    int divisor = std::numeric_limits<int>::min();
    std::cout << dividend << " / " << divisor << " = " << solu.divide(dividend, divisor) << " | "
            << (dividend) / (divisor) << std::endl;

    dividend = std::numeric_limits<int>::max();
    std::cout << dividend << " / " << divisor << " = " << solu.divide(dividend, divisor) << " | "
            << (dividend) / (divisor) << std::endl;

    divisor = std::abs(rand());
    std::cout << dividend << " / " << divisor << " = " << solu.divide(dividend, divisor) << " | "
                << (dividend) / (divisor) << std::endl;

    return 0;
}

