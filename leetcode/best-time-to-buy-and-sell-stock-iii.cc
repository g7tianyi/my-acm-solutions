#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int size = prices.size();
        if (size <= 1) {
            return 0;
        }

        vector<int> dp(size); // dp(i), max profit in [0, i]
        int minPrice = prices[0];
        int maxProfit = 0;
        dp[0] = 0;
        for (int i = 1; i < size; ++i) {
            if (maxProfit < prices[i] - minPrice) {
                maxProfit = prices[i] - minPrice;
            }
            dp[i] = maxProfit;
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            }
        }

        maxProfit = 0;
        int result = dp[size - 1];
        int maxPrice = prices[size - 1];
        for (int i = size - 2; i >= 0; --i) {
            if (maxProfit < maxPrice - prices[i]) {
                maxProfit = maxPrice - prices[i];
            }
            if (result < maxProfit + dp[i]) {
                result = maxProfit + dp[i];
            }
            if (maxPrice < prices[i]) {
                maxPrice = prices[i];
            }
        }

        return result;
    }
};
Solution solu;

int main() {

    vector<int> price;
    price.push_back(1), price.push_back(2), price.push_back(4);
    std::cout << solu.maxProfit(price) << std::endl;

    return 0;
}

