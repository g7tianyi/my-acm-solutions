#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_map>
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> result;
        int size = strs.size();
        if (size <= 1) { // WA for < 1... >_<
            return result;
        }

        std::unordered_map<string, int> anagram;
        for (int i = 0, j; i < size; ++i) {
            string str(strs[i]);
            std::sort(str.begin(), str.end());
            if (anagram.find(str) == anagram.end()) {
                anagram.insert(std::make_pair(str, i));
            } else {
                j = anagram[str];
                if (j >= 0) {
                    result.push_back(strs[j]);
                    anagram[str] = -1;
                }
                result.push_back(strs[i]);
            }
        }

        return result;
    }
};

Solution solu;

#include <ctime>

int myrandom(int i) {
    return std::rand() % i;
}

int main() {
    vector<string> strs;
    unsigned seed = (unsigned) time(0);
    srand(seed);
    string options[6] = { "hello", "world", "string", "main", "cplusplus", "algorithm" };
    for (int i = 0; i < 6; ++i) {
        string text = options[i];
        if (rand() & 0x1u) {
            int t = 1 + rand() % 6;
            while (t--) {
                std::random_shuffle(text.begin(), text.end(), myrandom);
                strs.push_back(text);
            }
        }
    }
    std::random_shuffle(strs.begin(), strs.end(), myrandom);

    printf("Input:\n");
    std::copy(strs.begin(), strs.end(), std::ostream_iterator<string>(std::cout, " "));
    std::cout << std::endl;
    vector<string> result = solu.anagrams(strs);
    printf("Found %lu results:\n", result.size());
    std::copy(result.begin(), result.end(), std::ostream_iterator<string>(std::cout, "\n"));

    return 0;
}

