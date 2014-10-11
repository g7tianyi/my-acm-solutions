#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    string addBinary(string left, string right) {
        if (left.empty()) {
            return right;
        }
        if (right.empty()) {
            return left;
        }

        string result;
        int carry(0);
        int i = left.size() - 1, j = right.size() - 1;
        int lnum, rnum, sum; // left number, right number, sum
        while (i >= 0 && j >= 0) {
            lnum = (left[i] - '0'), rnum = (right[j] - '0');
            sum = lnum + rnum + carry;
            result += ((sum & 0x1u) + '0');
            carry = sum >> 1;
            --i, --j;
        }

        while (i >= 0) {
            lnum = (left[i] - '0');
            result += ((lnum ^ carry) + '0');
            carry &= lnum;
            --i;
        }

        while (j >= 0) {
            rnum = (right[j] - '0');
            result += ((rnum ^ carry) + '0');
            carry &= rnum;
            --j;
        }

        if (carry) {
            result += (carry + '0');
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

Solution solu;

int main() {

    std::cout << "0" << " + " << "1" << " = " << solu.addBinary("0", "1")
            << std::endl;

    std::cout << "11" << " + " << "1" << " = " << solu.addBinary("11", "1")
            << std::endl;

    std::cout << "11" << " + " << "11" << " = " << solu.addBinary("11", "11")
            << std::endl;

    std::cout << "11" << " + " << "101" << " = " << solu.addBinary("11", "101")
            << std::endl;

    std::cout << "" << " + " << "11" << " = " << solu.addBinary("", "11")
            << std::endl;

    std::cout << "11" << " + " << "" << " = " << solu.addBinary("11", "")
            << std::endl;

    std::cout << "1000000011111" << " + " << "1111111111111" << " = "
            << solu.addBinary("1000000011111", "1111111111111") << std::endl;

    return 0;
}

