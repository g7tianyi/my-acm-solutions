#include <algorithm>
#include <iostream>

#include <vector>
using std::vector;

struct Worker {
    Worker(int key_, vector<int>& count_, vector<int>& option_, vector<vector<int> >& result_) :
            key(key_), count(count_), option(option_), result(result_) {
    }

    void combine(int pos, int curr, vector<int>& V) {
        if (curr == key) {
            vector<int> C(V);
            result.push_back(C);
            return;
        }
        if (pos == count.size()) {
            return;
        }

        int i, next;
        for (i = 0; i <= count[pos]; ++i) {
            next = curr + i * option[pos];
            if (key - next != 0 && key - next < option[pos]) {
                // pruning, since the option numbers are sorted
                break;
            }
            combine(pos + 1, next, V);
            V.push_back(option[pos]);
        }
        while (i > 0) {
            i--;
            V.pop_back();
        }
    }

private:
    int key;
    vector<int>& count;
    vector<int>& option;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int>& option, int key) {
        std::sort(option.begin(), option.end());
        vector<int> count;
        int cnt = 1;
        for (int i = 1; i < option.size(); ++i) {
            if (option[i] != option[i - 1]) {
                count.push_back(cnt);
                cnt = 1;
            } else {
                ++cnt;
            }
        }
        count.push_back(cnt);
        std::unique(option.begin(), option.end());

        vector<vector<int> > result;
        Worker worker(key, count, option, result);
        vector<int> V;
        worker.combine(0, 0, V);
        return result;
    }
};

Solution solu;

int main() {

    vector<int> option;

    //10,1,2,7,6,1,5
    option.push_back(10);
    option.push_back(1), option.push_back(2), option.push_back(7);
    option.push_back(6), option.push_back(1), option.push_back(5);

    vector<vector<int> > result = solu.combinationSum2(option, 8);
    int size = result.size();
    std::cout << "result count: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    option.clear();
    result = solu.combinationSum2(option, 8);
    size = result.size();
    std::cout << "result count: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

