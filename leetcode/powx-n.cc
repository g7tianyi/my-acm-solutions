#include <iostream>

class Solution {
public:
    double pow(double number, int exponent) {
        if (exponent == 0) {
            return 1;
        }

        bool negexp = false;
        if (exponent < 0) {
            negexp = true;
            exponent *= -1;
        }

        double result;
        if (exponent == 1) {
            result = number;
        } else {
            result = pow(number, exponent >> 1);
            result *= result;
            if (exponent & 0x1u) {
                result *= number;
            }
        }
        if (negexp) {
            return 1 / result;
        }
        return result;
    }
};

Solution solu;

int main() {
    std::cout << solu.pow(1.23, 10) << std::endl;
    std::cout << solu.pow(1.413, 5) << std::endl;
    std::cout << solu.pow(15.18, 1) << std::endl;
    std::cout << solu.pow(34.00515, 0) << std::endl;
    std::cout << solu.pow(34.00515, -1) << std::endl;
    std::cout << solu.pow(34.00515, -3) << std::endl;
    return 0;
}

