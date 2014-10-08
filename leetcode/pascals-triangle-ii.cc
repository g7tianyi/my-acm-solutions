#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> V;
        V.push_back(1);
        if (rowIndex <= 0) {
            return V;
        }
        for (int i = 1; i <= rowIndex; ++i) {
            int prev = V[0], curr;
            for (int j = 1; j < i; ++j) {
                curr = V[j];
                V[j] += prev;
                prev = curr;
            }
            V.push_back(1);
        }
        return V;
    }
};
Solution solution;

void test(int rowIndex) {
    vector<int> v = solution.getRow(rowIndex);
    std::cout << "Row " << rowIndex << ": ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        test(i);
    }
    return 0;
}

