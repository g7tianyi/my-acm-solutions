#include <iostream>
#include <string>
using std::string;

#include <vector>
using std::vector;

struct Worker {
    int optionCount;
    vector<int>& option;
    vector<vector<int> >& result;
    Worker(int optionCount_, vector<int>& option_,
            vector<vector<int> >& result_) :
            optionCount(optionCount_), option(option_), result(result_) {
    }

    void combine(int pos, int target, vector<int>& C) {
        if (target < 0 || pos >= optionCount) {
            return;
        }

        int j = 0, next;
        vector<int> R(C);
        while (true) {
            next = target - j * option[pos];
            if (next == 0) {
                result.push_back(R);
                break;
            }

            ++j;
            if (next > option[pos]) {
                combine(pos + 1, next, R);
                R.push_back(option[pos]);
            } else if (next == option[pos]) {
                R.push_back(option[pos]);
            } else {
                // since the options are sorted,
                // the latters can't do any help
                break;
            }
        }
    }
};

class Solution {
public:
    vector<vector<int> > combinationSum(vector<int>& option, int target) {
        vector<vector<int> > result;
        if (option.empty()) {
            return result;
        }

        std::sort(option.begin(), option.end());
        vector<int>::iterator pos = std::unique(option.begin(), option.end());
        int size = pos - option.begin();

#ifdef __LOCAL_DEBUG__
        std::cout << target << " <= { ";
        std::copy(option.begin(), option.begin() + size,
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << " }" << std::endl;
#endif

        vector<int> temp;
        Worker worker(size, option, result);
        worker.combine(0, target, temp);
        return result;
    }
};
Solution sol;

#define RANDOM_TEST

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

vector<int> V;

void print_input(vector<int>& options, int target) {
    std::cout << target << " <= { ";
    std::copy(options.begin(), options.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << " }" << std::endl;
}

void print_output(vector<vector<int> >& combination) {
    for (int i = 0; i < combination.size(); ++i) {
        std::copy(combination[i].begin(), combination[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test() {
    V.clear();
    V.push_back(2), V.push_back(3), V.push_back(6), V.push_back(7);
    print_input(V, 7);
    vector<vector<int> > reuslt = sol.combinationSum(V, 7);
    print_output(reuslt);
}

void test_random() {
    V.clear();
    srand((unsigned) time(0));
    for (int i = 0; i < 10; ++i) {
        V.push_back(1 + std::abs(rand()) % 20);
    }
    int target = std::abs(rand()) % 50;
    print_input(V, target);
    vector<vector<int> > result = sol.combinationSum(V, target);
    print_output(result);
}

int main() {
    test();
    for (int i = 0; i < 10; ++i) {
        test_random();
        usleep(1000 * 1000);
    }
    return 0;
}

