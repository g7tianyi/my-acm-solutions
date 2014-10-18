#include <iostream>

#include <unordered_map>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int lengthOfLongestSubstring(string str) {
        if (str.empty()) {
            return 0;
        }
        int size = str.size();
        if (size == 1) {
            return 1;
        }

        vector<int> start(size, 0); // can be optimized to constant space
        std::unordered_map<char, int> exists;

        start[0] = 0;
        exists.insert(std::make_pair(str[0], 0));
        int result = 1;
        bool appeared;
        for (int i = 1; i < size; ++i) {
            appeared = exists.find(str[i]) != exists.end();

            if (appeared && exists[str[i]] >= start[i - 1]) {
                start[i] = exists[str[i]] + 1;
            } else {
                start[i] = start[i - 1];
            }

            if (appeared) {
                exists[str[i]] = i;
            } else {
                exists.insert(std::make_pair(str[i], i));
            }

            result = std::max(result, i - start[i] + 1);
        }
        return result;
    }
};

Solution solu;

int main() {
    std::cout << solu.lengthOfLongestSubstring("abacdadc") << std::endl;
    std::cout << solu.lengthOfLongestSubstring("aaaaaaaaaaaaaaaa") << std::endl;
    std::cout << solu.lengthOfLongestSubstring("abcdefghijklmnopqrstuvwxyz") << std::endl;
    return 0;
}

