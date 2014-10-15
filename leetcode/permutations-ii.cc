#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

struct DFSRunner {
    DFSRunner(int size_, vector<int>& count_, vector<int>& option_, vector<vector<int> >& result_) :
        size(size_), count(count_), option(option_), result(result_) {
    }

    void run(int depth, vector<int>& vec) {
        if (depth == size) {
            vector<int> C(vec);
            result.push_back(C);
            return;
        }

        for (int i = 0; i < count.size(); ++i) {
            if (count[i]) {
                --count[i];
                vec.push_back(option[i]);
                run(depth + 1, vec);
                vec.pop_back();
                ++count[i];
            }
        }
    }

    int size;
    vector<int>& count;
    vector<int>& option;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& option) {
        vector<vector<int> > result;
        if (option.empty()) {
            return result;
        }

        std::sort(option.begin(), option.end());
        vector<int> count;
        int prev = option[0], cnt = 1, size = option.size();
        for (int i = 1; i < size; ++i) {
            if (option[i] != prev) {
                count.push_back(cnt);
                prev = option[i];
                cnt = 1;
            } else {
                ++cnt;
            }
        }
        count.push_back(cnt);
        std::unique(option.begin(), option.end());

        DFSRunner runner(size, count, option, result);
        vector<int> V;
        runner.run(0, V);
        return result;
    }
};

Solution solu;

int main() {
    vector<int> V;
    vector<vector<int> > result;

    V.push_back(1), V.push_back(2), V.push_back(1);
    result = solu.permuteUnique(V);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    V.clear();
    V.push_back(1), V.push_back(1), V.push_back(1),  V.push_back(1), V.push_back(1);
    result = solu.permuteUnique(V);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    V.push_back(2);
    result = solu.permuteUnique(V);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    V.clear();
    V.push_back(1), V.push_back(2), V.push_back(3);
    result = solu.permuteUnique(V);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

