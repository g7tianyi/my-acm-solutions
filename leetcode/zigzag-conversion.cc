#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    string convert(string str, int nRows) {
        if (nRows <= 1) {
            return str;
        }
        string result;
        if (str.empty()) {
            return result;
        }
        for (int i = 0; i < nRows; i++) {
            for (int j = 0, index = i; index < str.size(); j++, index = (2 * nRows - 2) * j + i) {
                result.append(1, str[index]);
                if (i == 0 || i == nRows - 1) {
                    continue;
                }
                if (index + (nRows - i - 1) * 2 < str.size()) {
                    result.append(1, str[index + (nRows - i - 1) * 2]);
                }
            }
        }
        return result;
    }
};

Solution solu;

int main() {

    std::cout << solu.convert("PAYPALISHIRING", 3) << std::endl;
    std::cout << solu.convert("PAYPALISHIRING", 4) << std::endl;
    std::cout << solu.convert("PAYPALISHIRING", 5) << std::endl;

    return 0;
}

