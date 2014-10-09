#include <iostream>

inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}

#include <vector>
using std::vector;
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) {
        if (obstacleGrid.empty()) {
            return 0;
        }
        if (obstacleGrid[0].empty()) {
            return 0;
        }

        int numRow = obstacleGrid.size(), numColumn = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[numRow - 1][numColumn - 1] ) {
            return 0;
        }
        dp[0][0] = 1;
        for (int i = 1; i < numRow; ++i) {
            dp[i][0] = (!obstacleGrid[i - 1][0]) && dp[i - 1][0];
        }
        for (int i = 1; i < numColumn; ++i) {
            dp[0][i] = (!obstacleGrid[0][i - 1]) && dp[0][i - 1];
        }

        int top, left;
        for (int i = 1; i < numRow; ++i) {
            for (int j = 1; j < numColumn; ++j) {
                top  = obstacleGrid[i - 1][j] ? 0 : dp[i - 1][j];
                left = obstacleGrid[i][j - 1] ? 0 : dp[i][j - 1];
                dp[i][j] = top + left;
            }
        }

        return dp[numRow - 1][numColumn - 1];
    }
private:
    int dp[102][102];
};
Solution sol;

int main() {
    vector<vector<int> > grid;
    vector<int> V0; V0.push_back(0); V0.push_back(0); V0.push_back(0);
    vector<int> V1; V1.push_back(0); V1.push_back(1); V1.push_back(0);
    vector<int> V2; V2.push_back(0); V2.push_back(0); V2.push_back(0);
    grid.push_back(V0), grid.push_back(V1), grid.push_back(V2);
    std::cout << sol.uniquePathsWithObstacles(grid) << std::endl;
    return 0;
}


