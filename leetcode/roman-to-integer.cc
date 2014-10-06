#include <string>
#include <iostream>
#include <algorithm>

using std::string;

class Solution {
public:
    int romanToInt(string str) {
        int map[26];
        map['I' - 'A'] = 1;
        map['V' - 'A'] = 5;
        map['X' - 'A'] = 10;
        map['L' - 'A'] = 50;
        map['C' - 'A'] = 100;
        map['D' - 'A'] = 500;
        map['M' - 'A'] = 1000;
        int res = 0, n = str.size();
        str.push_back(str[n - 1]);
        for (int i = 0; i < n; i++) {
            if (map[str[i] - 'A'] >= map[str[i + 1] - 'A'])
                res += map[str[i] - 'A'];
            else
                res -= map[str[i] - 'A'];
        }
        return res;
    }
};

Solution solution;

int main() {
    printf("%d\n", solution.romanToInt("XI"));
    return 0;
}

