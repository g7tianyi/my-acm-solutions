#include <vector>
using std::vector;

class Solution {
public:
    void setZeroes(vector<vector<int> >& matrix) {
        int numRow = matrix.size(), numColumn;
        for (int i = 0; i < numRow; ++i) {
            numColumn = matrix[i].size();
            for (int j = 0; j < numColumn; ++j) {
                // Note: if numbers are larger than INT_MAX / 2, we are doomed...
                matrix[i][j] <<= 1;
            }
        }

        for (int i = 0; i < numRow; ++i) {
            numColumn = matrix[i].size();
            for (int j = 0; j < numColumn; ++j) {
                if (matrix[i][j] == 0) {
                    dyeing(matrix, i, j);
                }
            }
        }

        for (int i = 0; i < numRow; ++i) {
            numColumn = matrix[i].size();
            for (int j = 0; j < numColumn; ++j) {
                matrix[i][j] >>= 1;
            }
        }

    }
private:
    void dyeing(vector<vector<int> >& matrix, int row, int column) {
        int numColumn = matrix[row].size();
        for (int i = 0; i < numColumn; ++i) {
            matrix[row][i] = 1;
        }
        int numRow = matrix.size();
        for (int i = 0; i < numRow; ++i) {
            matrix[i][column] = 1;
        }
    }
};

