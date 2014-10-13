#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

#define ABS(X) ((X) > 0 ? (X) : -(X))
static const float EPSILON = 0.000000001;

class Solution {
public:
    int sqrt(int x) {
        if (x == 0) {
            return x;
        }

        float dividend = x, divisor = x, prev;
        do {
            prev = divisor;
            divisor = (divisor + dividend / divisor) / 2;
        } while (ABS(divisor - prev) > EPSILON);

        int result = static_cast<int>(divisor);
        if (result * result > x) {
            --result;
        }
        return result;
    }
};

Solution solu;

vector<int> option;

int main() {
    std::cout << solu.sqrt(12345) << std::endl;
    std::cout << solu.sqrt(123456789) << std::endl;

    return 0;
}

