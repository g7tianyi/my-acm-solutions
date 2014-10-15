//#include <algorithm>

#include <iostream>

//#include <string>
//using std::string;

//#include <vector>
//using std::vector;

#include <limits>

class Solution {
public:
    int atoi(const char* str) {
        int result = 0;
        bool negative = false;
        while (isspace(*str)) {
            ++str;
        }

        if (*str == '+') {
            negative = false;
            ++str;
        } else if (*str == '-') {
            negative = true;
            ++str;
        }

        int num;
        if (negative) {
            while (isdigit(*str)) {
                num = *str - '0';
                if (result < std::numeric_limits<int>::min() / 10) {
                    result = std::numeric_limits<int>::min();
                    break;
                }
                result *= 10;
                if (result < std::numeric_limits<int>::min() + num) {
                    result = std::numeric_limits<int>::min();
                    break;
                }
                result -= num;
                ++str;
            }
        } else {
            while (isdigit(*str)) {
                num = *str - '0';
                if (result > std::numeric_limits<int>::max() / 10) {
                    result = std::numeric_limits<int>::max();
                    break;
                }
                result *= 10;
                if (result > std::numeric_limits<int>::max() - num) {
                    result = std::numeric_limits<int>::max();
                    break;
                }
                result += num;
                ++str;
            }
        }
        return result;
    }
};

Solution solu;


int main() {

    std::cout << solu.atoi("-1287466145176248") << std::endl;
    std::cout << solu.atoi("-128746 6145176248") << std::endl;
    std::cout << solu.atoi("812745761245") << std::endl;
    std::cout << solu.atoi("81271245") << std::endl;
    std::cout << solu.atoi("8127 1245") << std::endl;
    std::cout << solu.atoi("8127$45") << std::endl;

    return 0;
}

