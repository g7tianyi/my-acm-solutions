#include <iostream>

inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}

#include <string>
using std::string;

class Solution {
public:
    string countAndSay(int n) {
        string text = "1";
        if (n <= 1) {
            return text;
        }

        string next;
        for (int i = 2; i <= n; ++i) {
            size_t len = text.length();
            char curr = text[0];
            int count = 1;
            for (size_t j = 1; j < len; ++j) {
                if (text[j] != curr) {
                    concat(next, count, curr);
                    curr = text[j];
                    count = 1;
                } else {
                    ++count;
                }
            }
            concat(next, count, curr);
            text = next;
            next.clear();
        }
        return text;
    }
private:
    inline void concat(string& next, int count, char curr) {
        string temp;
        intToString(count, temp);
        temp += curr;
        next += temp;
    }
    inline void intToString(int num, string& str) {
        if (!num) {
            str += '0';
            return;
        }
        char ch;
        while (num) {
            ch = '0' + num % 10;
            str.insert(str.begin(), ch);
            num /= 10;
        }
    }
};
Solution sol;

int main() {
    for (int i = 1; i <= 20; ++i) {
        std::cout << sol.countAndSay(i) << std::endl;
    }
    return 0;
}

