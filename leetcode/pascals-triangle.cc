#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using std::vector;

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > R;
        for (int i = 0; i < numRows; ++i) {
            vector<int> V;
            V.push_back(1);
            if (i == 0) {
                R.push_back(V);
                continue;
            }
            for (int j = 1; j < i; ++j) {
                V.push_back(R[i - 1][j - 1] + R[i - 1][j]);
            }
            V.push_back(1);
            R.push_back(V);
        }
        return R;
    }
};
static Solution solution;

namespace stest {

void run() {
    for (int i = 0; i <= 10; ++i) {
        vector<vector<int> > R = solution.generate(i);
        std::cout << i << "-d pascals-triangle:\n";
        for (int j = 0; j < R.size(); ++j) {
            std::copy(R[j].begin(), R[j].end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

}

int main() {
    stest::run();
    return 0;
}

