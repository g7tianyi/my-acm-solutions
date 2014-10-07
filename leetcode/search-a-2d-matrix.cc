#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    bool searchMatrix(vector<vector<int> >& matrix, int key) {
        int first = 0, last = matrix.size() - 1, mid;
        while (first <= last) {
            mid = mean(first, last);
            if (matrix[mid][0] == key) {
                return true;
            } else if (matrix[mid][0] < key) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }

        // return last we get the one that most closes to yet less than the key
        // return first we get the one that most closes to yet larger than the key
        int row = last;
        if (row < 0) {
            return false;
        }

        first = 0, last = matrix[row].size() - 1;
        while (first <= last) {
            mid = mean(first, last);
            if (matrix[row][mid] == key) {
                return true;
            } else if (matrix[row][mid] < key) {
                first = mid + 1;
            } else {
                last = mid - 1;
            }
        }
        return false;
    }
private:
    inline int mean(int small, int large) {
        return small + ((large - small) >> 1);
    }
};
static Solution solution;

namespace stest {

const int MAX_RAND = 999;

static vector<vector<int> > mockData(int m, int n) {
    int total = m * n;
    vector<int> V;
    srand((unsigned) time(0));
    for (int i = 0; i < total; ++i) {
        V.push_back(std::abs(rand()) % MAX_RAND);
    }
    std::sort(V.begin(), V.end());

    vector<vector<int> > matrix;
    for (int i = 0, k = 0; i < n; ++i) {
        vector<int> M;
        for (int j = 0; j < m; ++j) {
            M.push_back(V[k++]);
        }
        matrix.push_back(M);
    }
    return matrix;
}

static void printMatrix(vector<vector<int> >& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        std::copy(matrix[i].begin(), matrix[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}

void test(int m, int n) {
    vector<vector<int> > matrix = mockData(m, n);
    std::cout << ">>> matrix:\n";
    printMatrix(matrix);
    srand((unsigned) time(0));
    for (int i = 0, num; i < 10; ++i) {
        num = std::abs(rand()) % MAX_RAND;
        std::cout << ">>> searching " << num << " => "
                << (solution.searchMatrix(matrix, num) ? "found" : "not found")
                << std::endl;
    }
    int num = MAX_RAND << 1;
    std::cout << ">>> searching " << num << " => "
            << (solution.searchMatrix(matrix, num) ? "found" : "not found")
            << std::endl;

    std::cout << std::endl;
}

void run() {
    test(1, 1);
    test(7, 9);
    test(1, 10);
    test(100, 100);
}

}

int main() {
    stest::run();
    return 0;
}

