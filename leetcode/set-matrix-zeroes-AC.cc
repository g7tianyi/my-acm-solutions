#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    void setZeroes(vector<vector<int> >& matrix) {
        int numRow = matrix.size();
        if (numRow == 0) {
            return;
        }
        int numColumn = matrix[0].size();
        if (numColumn == 0) {
            return;
        }

        bool zeroRow0 = false;
        for (int i = 0; i < numColumn; ++i) {
            if (matrix[0][i] == 0) {
                zeroRow0 = true;
                break;
            }
        }
        bool zeroColumn0 = false;
        for (int i = 0; i < numRow; ++i) {
            if (matrix[i][0] == 0) {
                zeroColumn0 = true;
                break;
            }
        }

        for (int i = 1; i < numRow; ++i) {
            for (int j = 1; j < numColumn; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0, matrix[0][j] = 0;
                }
            }
        }

        // dyeing
        for (int i = 1; i < numRow; ++i) {
            for (int j = 1; j < numColumn; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (zeroRow0) {
            for (int i = 0; i < numColumn; ++i) {
                matrix[0][i] = 0;
            }
        }
        if (zeroColumn0) {
            for (int i = 0; i < numRow; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};

static Solution solution;

namespace stest {

vector<vector<int> > V;

enum {
    ZERO_ODD = 10, SIGN_ODD = 10, MAX_RAND = 99
};

static void mockData(int numRow, int numColumn) {
    V.clear();
    srand((unsigned) time(0));
    for (int i = 0; i < numRow; ++i) {
        bool signFlag, zeroFlag;
        vector<int> C;
        for (int j = 0, num; j < numColumn; ++j) {
            zeroFlag = rand() % ZERO_ODD == 0;
            if (zeroFlag) {
                C.push_back(0);
            } else {
                num = rand() % MAX_RAND;
                signFlag = rand() % SIGN_ODD == 0;
                if (signFlag) {
                    num *= -1;
                }
                C.push_back(num);
            }
        }
        V.push_back(C);
    }
}
static void print() {
    int numRow = V.size();
    for (int i = 0; i < numRow; ++i) {
        std::copy(V[i].begin(), V[i].end(),
                std::ostream_iterator<int>(std::cout, "\t"));
        std::cout << std::endl;
    }
}
static void test(int numRow, int numColumn) {
    mockData(numRow, numColumn);
    std::cout << "Original Matrix:\n";
    print();
    std::cout << "Rendered Matrix:\n";
    solution.setZeroes(V);
    print();
    std::cout << std::endl;
}

void run() {
    test(1, 1);
    test(1, 10);
    test(10, 1);
    test(3, 5);
    test(6, 4);
    test(4, 5);
    test(7, 7);
    test(21, 19);
    test(100, 100);
}

}

int main() {
    stest::run();
    return 0;
}

