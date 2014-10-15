//#include <algorithm>

#include <iostream>

//#include <string>
//using std::string;

#include <vector>
using std::vector;

typedef vector<int>::iterator vecIterator;

struct DFSRunner {
    DFSRunner(vector<int>& option_, vector<vector<int> >& result_) :
        option(option_), result(result_) {
    }

    void run(int target, int depth, int start, vector<int>& V) {
        if (depth == 3) {
            vecIterator pos = binarySearch(option.begin() + start, option.end() - 1, target);
            if (pos != option.end()) {
                vector<int> C(V);
                C.push_back(*pos);
                result.push_back(C);
            }
            return;
        }

        for (int i = start; i < static_cast<int>(option.size()) + depth - 3; ++i) {
            if (target - option[i] >= option[i]) { // vector option are sorted
                V.push_back(option[i]);
                run(target - option[i], depth + 1, i + 1, V);
                V.pop_back();
            }
        }
    }

    vector<int>& option;
    vector<vector<int> >& result;
private:
    // first and last are both closed => [first, last]
    vecIterator binarySearch(vecIterator first, vecIterator last, int key) {
        vecIterator mid, failure = last + 1;
        while (first <= last) {
            mid = first + ((last - first) >> 1);
            if (*mid == key) {
                return mid;
            } else if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }
        return failure;
    }
};

class Solution {
public:
    vector<vector<int> > fourSum(vector<int>& num, int target) {
        vector<vector<int> > result;
        if (num.empty()) {
            return result;
        }

        std::sort(num.begin(), num.end());
        DFSRunner runner(num, result);
        vector<int> V;
        runner.run(target, 0, 0, V);
        return result;
    }
};

Solution solu;

vector<int> option;
vector<vector<int> > result;

int main() {
    option.push_back(1), option.push_back(0), option.push_back(-1);
    option.push_back(0), option.push_back(2), option.push_back(-2);

    result = solu.fourSum(option, 0);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    option.clear();
    option.push_back(0);
    result = solu.fourSum(option, 0);
    std::cout << "--------" << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

