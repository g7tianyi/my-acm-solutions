#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        if (n < 0) {
            return result;
        }
        result.push_back(0);
        int count = 1, size;
        for (int i = 0, j; i < n; ++i) {
            count <<= 1;
            size = result.size();
            for (j = size - 1; j >= 0; --j) {
                result.push_back((1 << i) | result[j]);
            }
        }

        return result;
    }
};

Solution solu;

#include <bitset>
int main() {
    vector<int> result;
    for (int i = 0; i <= 10; ++i) {
        result = solu.grayCode(i);
        std::cout << "Gray Code " << i << std::endl;
        for (int j = 0; j < result.size(); ++j) {
            std::cout << std::bitset<20>(result[j]) << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

