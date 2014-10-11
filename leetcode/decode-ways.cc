#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) {
            return 0;
        }
        int size = s.size();
        vector<int> dp(size, 0);

        dp[0] = (s[0] != '0') ? 1 : 0;
        for (int i = 1; i < size; ++i) {
            if (s[i] != '0') {
                dp[i] += dp[i - 1];
            }
            if (s[i - 1] != '0' && toNumber(s[i - 1], s[i]) <= 26) {
                dp[i] += (i > 1 ? dp[i - 2] : 1);
            }
        }
        return dp[size - 1];
    }
private:
    inline int toNumber(char prev, char curr) {
        return (prev - '0') * 10 + (curr - '0');
    }
};

Solution solu;

int main() {
    std::cout << solu.numDecodings("0") << std::endl;
    std::cout << solu.numDecodings("12") << std::endl;
    std::cout << solu.numDecodings("120") << std::endl;
    std::cout << solu.numDecodings("1221") << std::endl;
    std::cout << solu.numDecodings("12210") << std::endl;
    std::cout << solu.numDecodings("122101") << std::endl;
    std::cout << solu.numDecodings("122101221") << std::endl;
    return 0;
}

