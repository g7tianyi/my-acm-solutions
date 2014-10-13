#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    typedef vector<int>::iterator iterator;
    vector<vector<int> > threeSum(vector<int>& option) {
        vector<vector<int> > result;

        if (option.empty()) {
            return result;
        }

        iterator first = option.begin(), last = option.end();
        std::sort(first, last);

        int size = option.size();
        int key, prei, prej;
        for (int i = 0; i < size - 2; ++i) {
            if (i > 0 && prei == option[i]) {
                continue;
            }
            prei = option[i];

            for (int j = i + 1; j < size - 1; ++j) {
                if (j > i + 1 && prej == option[j]) {
                    continue;
                }
                prej = option[j];

                key = -(option[i] + option[j]);
                // watch out for the details, must be (last - 1)
                if (binarySearch(first + j + 1, last - 1, key)) {
                    vector<int> v;
                    v.push_back(option[i]);
                    v.push_back(option[j]);
                    v.push_back(key);
                    result.push_back(v);
                }
            }
        }
        return result;
    }
private:
    // first and last are both closed => [first, last]
    bool binarySearch(iterator first, iterator last, int key) {
        iterator mid;
        while (first <= last) {
            mid = first + ((last - first) >> 1);
            if (*mid == key) {
                return true;
            } else if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }
        return false;
    }
};

Solution solu;

vector<int> option;

int main() {
    option.push_back(-1), option.push_back(0),  option.push_back(1);
    option.push_back(2),  option.push_back(-1), option.push_back(-4);
    option.push_back(-2), option.push_back(-2), option.push_back(3);
    option.push_back(0),  option.push_back(-4), option.push_back(3);
    vector<vector<int> > result = solu.threeSum(option);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    option.clear();
    option.push_back(2),  option.push_back(0),  option.push_back(-2);
    option.push_back(-5), option.push_back(-5), option.push_back(-3);
    option.push_back(2),  option.push_back(-4);

    result = solu.threeSum(option);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

