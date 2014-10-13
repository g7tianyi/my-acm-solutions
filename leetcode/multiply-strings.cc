#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    string multiply(string num1, string num2) {
        int size1 = num1.size(), size2 = num2.size();
        if (size1 <= 0 || size2 <= 0) {
            return "0";
        }

        vector<int> left(size1, 0);
        vector<int> right(size2, 0);

        for (int i = 0; i < size1; ++i) {
            left[i] = num1[size1 - 1 - i] - '0';
        }
        for (int i = 0; i < size2; ++i) {
            right[i] = num2[size2 - 1 - i] - '0';
        }

        int size = size1 * size2 + 1;
        vector<int> result(size, 0);
        for (int i = 0; i < size1; ++i) {
            for (int j = 0; j < size2; ++j) {
                result[i + j] += left[i] * right[j];
            }
        }

        for (int i = 0; i < size; ++i) {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }

        string product;
        bool found = false; // flag indicating if the highest position has been found
        for (int i = size - 1; i >= 0; --i) {
            if (!found && result[i]) {
                found = true;
            }
            if (found) {
                product += ('0' + result[i]);
            }
        }

        if (product.empty()) {
            product = "0";
        }

        return product;
    }
};

Solution solu;

string pairs[][2] = {
    { "0", "0" },
    { "0", "12312426457568769634" },
    { "123", "456" },
    { "123456789", "123456789" },
    { "1", "456" },
    { "9", "9" },
    { "123", "1" },
    { "112489236417523", "19248612451878" },
    { "11248054692306417523", "192408612440670518780" },
};

int main() {
    for (int i = 0; i < 8; ++i) {
        std::cout << pairs[i][0] << " * " << pairs[i][1] << " = "
                << solu.multiply(pairs[i][0], pairs[i][1]) << std::endl;
    }
    return 0;
}

