#include <iostream>
#include <algorithm>

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 0) {
            return 0;
        }
        int f1 = 1, f2 = 2;
        if (n == 1) {
            return f1;
        }
        // DP.
        // F(i) = F(i - 1) + F(i - 2),
        // means using one step from stair i - 1
        // or using two steps from stair i - 2
        for (int i = 3, f; i <= n; ++i) {
            f = f1 + f2;
            f1 = f2, f2 = f;
        }
        return f2;
    }
};

Solution solution;

int main() {
    printf("Testing %d stair  => %d\n", 0, solution.climbStairs(0));
    printf("Testing %d stair  => %d\n", 1, solution.climbStairs(1));
    printf("Testing %d stairs => %d\n", 2, solution.climbStairs(2));
    printf("Testing %d stairs => %d\n", 3, solution.climbStairs(3));
    printf("Testing %d stairs => %d\n", 4, solution.climbStairs(4));
    printf("Testing %d stairs => %d\n", 10, solution.climbStairs(10));
    return 0;
}

