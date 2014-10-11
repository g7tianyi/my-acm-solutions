#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

#define __LOCAL_MODE__
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        if (triangle.empty()) {
            return 0;
        }
        if (triangle[0].empty()) {
            return 0;
        }

        int numRow = triangle.size();
        vector<int> dp(numRow + 1, 0);
        dp[0] = triangle[0][0];

        int first, second, third, size;
        for (int i = 1; i < numRow; ++i) {
            size = triangle[i].size();
            first = dp[0], second = dp[1];
            dp[0] = triangle[i][0] + first;
            for (int j = 1; j < size - 1; ++j) {
                third = dp[j + 1];
                dp[j] = std::min(first, second) + triangle[i][j];
                first = second;
                second = third;
            }
            dp[size - 1] = triangle[i][size - 1] + first;
#ifdef __LOCAL_MODE__
            std::cout << "dp: ";
            std::copy(dp.begin(), dp.begin() + numRow,
                    std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
#endif
        }

        return *(std::min_element(dp.begin(), dp.begin() + numRow));
    }
};
Solution sol;

#define RANDOM_TEST

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

vector<vector<int> > V;

void print_input(vector<vector<int> >& triangle) {
    for (int i = 0; i < triangle.size(); ++i) {
        std::copy(triangle[i].begin(), triangle[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}

void test() {
    V.clear();
    vector<int> v0;
    v0.push_back(2), V.push_back(v0);
    vector<int> v1;
    v1.push_back(3), v1.push_back(4), V.push_back(v1);
    vector<int> v2;
    v2.push_back(6), v2.push_back(5), v2.push_back(7), V.push_back(v2);
    vector<int> v3;
    v3.push_back(4), v3.push_back(1), v3.push_back(8), v3.push_back(3), V.push_back(
            v3);
    print_input(V);
    std::cout << sol.minimumTotal(V) << std::endl;
}

int main() {
    test();
    return 0;
}

