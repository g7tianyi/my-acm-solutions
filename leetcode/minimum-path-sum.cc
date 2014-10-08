#include <vector>
using std::vector;

class Solution {
public:
    int minPathSum(vector<vector<int> >& grid) {
        int numRow = grid.size();
        if (numRow == 0) {
            return 0;
        }
        int numColumn = grid[0].size();
        if (numColumn == 0) {
            return 0;
        }

        for (int i = 1; i < numColumn; ++i) {
            grid[0][i] += grid[0][i - 1];
        }
        for (int i = 1; i < numRow; ++i) {
            grid[i][0] += grid[i - 1][0];
        }

        for (int i = 1; i < numRow; ++i) {
            for (int j = 1; j < numColumn; ++j) {
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }

        return grid[numRow - 1][numColumn - 1];
    }
private:
    inline int min(int a, int b) {
        return a < b ? a : b;
    }
};

