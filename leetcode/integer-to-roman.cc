#include <iostream>
#include <string>
using std::string;

const string symbol[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
class Solution {
public:
    string intToRoman(int num) {
        string str;
        int value[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
        for (int i = 0; num != 0; ++i) {
            while (num >= value[i]) {
                num -= value[i];
                str += symbol[i];
            }
        }
        return str;
    }
};

Solution solu;

int main() {
    std::cout << solu.intToRoman(1) << std::endl;
    std::cout << solu.intToRoman(11) << std::endl;
    std::cout << solu.intToRoman(1123) << std::endl;
    std::cout << solu.intToRoman(3999) << std::endl;
    return 0;
}

