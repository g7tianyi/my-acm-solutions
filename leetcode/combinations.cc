#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

struct Worker {
    Worker(int _maxnum, int _length, vector<vector<int> >& V) :
            maxnum(_maxnum), length(_length), result(V) {
    }
    void run(int start, int depth, vector<int>& V) {
        if (depth > length) {
            return;
        }
        if (depth == length) {
            vector<int> C(V);
            result.push_back(C);
            return;
        }
        for (int i = start; i <= maxnum; ++i) {
            V.push_back(i);
            run(i + 1, depth + 1, V);
            V.pop_back();
        }
    }

private:
    int maxnum, length;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > combine(int maxnum, int length) {
        vector<vector<int> > result;
        Worker worker(maxnum, length, result);
        vector<int> V;
        worker.run(1, 0, V);
        return result;
    }
};

static Solution solution;

void test(int n, int k) {
    vector<vector<int> > V = solution.combine(n, k);
    int size = V.size();
    std::cout << "Testing (" << n << ", " << k << "):\n";
    for (int i = 0; i < size; ++i) {
        std::copy(V[i].begin(), V[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j <= i; ++j) {
            test(i, j);
        }
    }
    return 0;
}

