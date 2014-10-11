#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int numRow = matrix.size(), numColumn = matrix[0].size();

        vector<vector<int> > dp;
        int i, j, result = 0;
        for (i = 0; i < numRow; ++i) {
            vector<int> v;
            for (j = 0; j < numColumn; ++j) {
                v.push_back(matrix[i][j] - '0');
            }
            result = std::max(result, maxarea(v, 1));
            dp.push_back(v);
        }

        for (int k = 1; k < numRow; ++k) { // height
            for (i = 0; i + k < numRow; ++i) {
                for (j = 0; j < numColumn; ++j) {
                    dp[i][j] += (matrix[i + k][j] - '0');
                }
                result = std::max(result, maxarea(dp[i], k + 1));
            }
        }

        return result;
    }
private:
    inline int maxarea(vector<int>& vec, int height) {
        int size = vec.size(), count = 0, length = 0;
        for (int i = 0; i < size; ++i) {
            if (vec[i] == height) {
                ++count;
            } else {
                length = std::max(length, count);
                count = 0;
            }
        }
        length = std::max(length, count);
        return length * height;
    }
};

Solution solu;

#include <ctime>
#include <unistd.h>

vector<vector<char> > matrix;

void init(int row, int column) {
    matrix.clear();
    usleep(1000 * 1000);
    srand((unsigned) time(0));
    for (int i = 0; i < row; ++i) {
        vector<char> v;
        for (int j = 0; j < column; ++j) {
            v.push_back((rand() % 4) ? '1' : '0');
        }
        matrix.push_back(v);
    }
}

void print() {
    for (int i = 0; i < matrix.size(); ++i) {
        std::copy(matrix[i].begin(), matrix[i].end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }
}

void test(int row, int column) {
    init(row, column);
    print();
    std::cout << solu.maximalRectangle(matrix) << std::endl;
    std::cout << std::endl;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            test(i, j);
        }
    }
    return 0;
}

