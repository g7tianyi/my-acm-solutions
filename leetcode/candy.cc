#include <iostream>
#include <string>
using std::string;

#include <numeric>
#include <vector>
using std::vector;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int size = ratings.size();
        if (size == 0) {
            return 0;
        }
        vector<int> dp(size, 1);
        for (int i = 1; i < size; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
        }
        dp[size - 1] = std::max(dp[size - 1], 1);
        for (int i = size - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                dp[i] = std::max(dp[i], dp[i + 1] + 1);
            }
        }
        return std::accumulate(dp.begin(), dp.end(), 0);
    }
};

Solution sol;

#define RANDOM_TEST

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

vector<int> V;

void print(int result) {
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << result;
    std::cout << std::endl;
}

void test1() {
    V.clear();
    print(sol.candy(V));

    V.push_back(1), V.push_back(3), V.push_back(8), V.push_back(6);
    V.push_back(2), V.push_back(9), V.push_back(7), V.push_back(4);
    print(sol.candy(V));

    V[0] = 10;
    print(sol.candy(V));

    V[7] = 10;
    print(sol.candy(V));
}

void test2(int count) {
    srand((unsigned) time(0));
    for (int i = 0; i < count; ++i) {
        int size = std::abs(rand()) % (count << 1);
        V.clear();
        for (int j = 0; j < size; ++j) {
            V.push_back(std::abs(rand()) % (count << 1));
        }
        print(sol.candy(V));
        usleep(1000 * 1000);
    }
}

int main() {
    test1();
    test2(15);
    return 0;
}

