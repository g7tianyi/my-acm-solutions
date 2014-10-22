#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    vector<string> restoreIpAddresses(string str) {
        return partition(str, 0, 4);
    }
private:
    vector<string> partition(string& str, int start, int part) {
        vector<string> result;
        int length = str.size() - start;
        if (length < part || length > part * 3) {
            return result;
        }

        int num = 0;
        if (part == 1) {
            for (int i = 0; i < length; ++i) {
                num = num * 10 + (str[start + i] - '0');
            }
            if (!(str[start] == '0' && (num || length > 1)) && num < 256) {
                // cases like 1.2.3.04, 1.2.3.004 is illegal
                result.push_back(str.substr(start, length));
            }
            return result;
        }

        for (int i = 0; i < 3; ++i) {
            num = num * 10 + (str[start + i] - '0');
            if (!(str[start] == '0' && (num || i)) && num < 256) {
                string curr = str.substr(start, i + 1);
                vector<string> subres = partition(str, start + i + 1, part - 1);
                for (int j = 0; j < subres.size(); ++j) {
                    result.push_back(curr + "." + subres[j]);
                }
            }
        }

        return result;
    }
};

Solution solu;

int main() {

    vector<string> testCase;
    testCase.push_back("255255255255");
    testCase.push_back("25525511135");
    testCase.push_back("2552551013");
    testCase.push_back("196128111");
    testCase.push_back("192128111");
    testCase.push_back("10101010");
    testCase.push_back("010010");
    testCase.push_back("12304");
    testCase.push_back("12034");
    testCase.push_back("1234");
    testCase.push_back("0000");
    testCase.push_back("341");
    testCase.push_back("1111111111111");
    testCase.push_back("");

    vector<string> result;

    for (vector<string>::iterator pos = testCase.begin(); pos != testCase.end();
            ++pos) {
        result = solu.restoreIpAddresses(*pos);
        std::copy(result.begin(), result.end(),
                std::ostream_iterator<string>(std::cout, "\n"));
        std::cout << "---------------" << std::endl;
    }

    return 0;
}

