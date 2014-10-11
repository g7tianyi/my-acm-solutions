#include <algorithm>
#include <iostream>
#include <string>
using std::string;
class Solution {
public:
    void reverseWords(string& text) {
        trim(text);
        size_t length = text.length();
        size_t first = 0, curr;
        for (curr = 0; curr < length; ++curr) {
            if (text[curr] == ' ' && first != curr) {
                std::reverse(text.begin() + first, text.begin() + curr);
                first = curr + 1;
            }
        }
        std::reverse(text.begin() + first, text.begin() + curr);
        std::reverse(text.begin(), text.end());
    }
private:
    void trim(string& text) {
        size_t size = text.size();
        int begin = 0, end = size - 1;
        while (begin < size && text[begin] == ' ') {
            ++begin;
        }
        while (end > begin && text[end] == ' ') {
            --end;
        }
        text = text.substr(begin, end + 1 - begin);

        size = text.size();
        int space = 0, i = 1, j = 1;
        for (; i < size; ++i) {
            if (text[i] == ' ') {
                ++space;
                if (space < 2) { // consecutively appeared more than once
                    text[j++] = text[i];
                }
            } else {
                space = 0;
                text[j++] = text[i];
            }
        }
        text = text.substr(0, j);
    }
};

Solution sol;

int main() {
    string text;

    text = "the sky is blue";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = "  the sky is blue";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = "the sky is blue   ";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = "  the  sky    is    blue   ";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = "                    ";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = "";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    text = " ";
    sol.reverseWords(text);
    std::cout << "reversed: " << '[' << text << ']' << std::endl;

    return 0;
}

