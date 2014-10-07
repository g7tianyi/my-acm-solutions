#include <algorithm>
#include <iostream>
#include <ctime>

class Solution {
public:
    int uniquePaths(int m, int n) {
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; ++i) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
private:
    int dp[102][102];
};
static Solution solution;

int main() {
    for (int i = 1; i < 100; ++i) {
        for (int j = 1; j < 100; ++j) {
            printf("Board (%d, %d) => %d\n", i, j, solution.uniquePaths(i, j));
        }
    }
    return 0;
}

