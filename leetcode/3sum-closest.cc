#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

#include <algorithm>
#include <vector>
using std::vector;

#include <unordered_set>
class Solution {
public:
    typedef vector<int>::iterator vecIter;
    int threeSumClosest(vector<int>& nums, int key) {
        if (nums.empty()) {
            return 0;
        }
        size_t size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        if (size == 2) {
            return nums[0] + nums[1];
        }

        std::sort(nums.begin(), nums.end());

        std::unordered_set<int> flag;
        int sub, opt, res = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < size - 2; ++i) {
            for (int j = i + 1; j < size - 1; ++j) {
                sub = nums[i] + nums[j];
                if (flag.find(sub) != flag.end()) {
                    continue;
                }
                flag.insert(sub);
                sub = key - sub;
                opt = binarySearch(nums.begin() + j + 1, nums.end() - 1, sub);
                if (std::abs(res - key) > std::abs(opt - sub)) {
                    res = opt - sub + key;
                }
                if (res == key) {
                    return res;
                }
            }
        }

        return res;
    }

    int binarySearch(vecIter first, vecIter last, int key) {
        vecIter begin = first, end = last, middle;
        while (begin <= end) {
            middle = begin + ((end - begin) >> 1);
            if (*middle == key) {
                return key;
            } else if (*middle < key) {
                begin = middle + 1;
            } else {
                end = middle - 1;
            }
        }
        if (begin > last) {
            return *last;
        }
        if (end < first) {
            return *first;
        }
        if (std::abs(*begin - key) < std::abs(*end - key)) {
            return *begin;
        } else {
            return *end;
        }
    }
};

Solution solu;

#include <ctime>
vector<int> vec;

void testCloseSearch() {
    vec.clear();
    srand((unsigned) time(0));
    for (int i = 1; i <= 20; ++i) {
        vec.push_back(i * i);
    }
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << 401 << " => " << solu.binarySearch(vec.begin(), vec.end() - 1, 401) << std::endl;
    std::cout << -2 << " => " << solu.binarySearch(vec.begin(), vec.end() - 1, -2) << std::endl;

    for (int i = 1, j; i <= 10; ++i) {
        j = rand() % 10;
        std::cout << i * i - j << " => " << solu.binarySearch(vec.begin(), vec.end() - 1, i * i - j)
                << std::endl;
        j = rand() % 10;
        std::cout << i * i + j << " => " << solu.binarySearch(vec.begin(), vec.end() - 1, i * i + j)
                << std::endl;
    }
}

int main() {
    //testCloseSearch();
    vec.clear();
    vec.push_back(-1), vec.push_back(2), vec.push_back(1), vec.push_back(-4);
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    printf("searching %d => %d\n\n", 1, solu.threeSumClosest(vec, 1));

    vec.clear();
    srand((unsigned) time(0));
    for (int i = 0; i < 10000; ++i) {
        vec.push_back(rand() % 10000);
    }
    int num = rand() % 100000;
    printf("searching %d => %d\n\n", num, solu.threeSumClosest(vec, num));

    return 0;
}

