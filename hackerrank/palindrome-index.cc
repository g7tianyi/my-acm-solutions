#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

bool palindrome(string str) {
    int i = 0, j = str.length() - 1;
    while (i < j) {
        if (str[i] != str[j])
            return false;
        i++, j--;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string str;
        cin >> str;
        int i = 0, j = str.length() - 1;
        int result = -1;
        while (i < j && str[i] == str[j]) {
            i++, j--;
        }
        if (i < j) {
            string str1 = str.substr(0, i) + str.substr(i + 1, str.length() - i - 1);
            if (palindrome(str1)) {
                result = i;
            }
            string str2 = str.substr(0, j) + str.substr(j + 1, str.length() - j - 1);
            if (palindrome(str2)) {
                result = j;
            }
        }
        cout << result << endl;
    }
    return 0;
}

