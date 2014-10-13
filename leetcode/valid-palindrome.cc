#include <algorithm>
#include <iostream>
#include <string>
using std::string;

class Solution {
public:
    bool isPalindrome(string text) {
        if (text.empty()) {
            return true;
        }

        int size = text.size();
        int i = 0, j = size - 1;
        char former, latter;
        while (i < j) {
            former = '#', latter = '#'; // watch out for the details
            while (i <= j && (former = normalize(text[i])) == '#') {
                ++i;
            }
            while (j >= i && (latter = normalize(text[j])) == '#') {
                --j;
            }
            //std::cout << i << ' ' << former << ' ' << j << ' ' << latter << std::endl;
            if (former == latter) {
                ++i, --j;
            } else {
                return false;
            }
        }
        return true;
    }
private:
    inline char normalize(char ch) {
        if (ch >= 'a' && ch <= 'z') {
            return ch;
        }
        if (ch >= '0' && ch <= '9') {
            return ch;
        }
        if (ch >= 'A' && ch <= 'Z') {
            return 'a' + (ch - 'A');
        }
        return '#';
    }
};

Solution solu;

int main() {
    string str;
    str = "A man, a plan, a canal: Panama";
    std::cout << "\"" << str << (solu.isPalindrome(str) ? "\" is " : "\" is not ") << "palindrome."
            << std::endl;

    str = "race a car";
    std::cout << "\"" << str << (solu.isPalindrome(str) ? "\" is " : "\" is not ") << "palindrome."
            << std::endl;

    str = ".,";
    std::cout << "\"" << str << (solu.isPalindrome(str) ? "\" is " : "\" is not ") << "palindrome."
            << std::endl;

    str = "\"\"Sue,\" Tom smiles, \"Selim smote us.\"\"";
    std::cout << "\"" << str << (solu.isPalindrome(str) ? "\" is " : "\" is not ") << "palindrome."
            << std::endl;
    return 0;
}

