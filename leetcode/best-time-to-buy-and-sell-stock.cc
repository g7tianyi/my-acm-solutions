#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if (size <= 1) {
            return 0;
        }

        int prev = prices[0], next;
        for (int i = 1; i < size; ++i) {
            next = prices[i] - prev;
            prev = prices[i];
            prices[i] = next;
        }

        // DP.
        int maxTotal = prices[1], maxCurr = prices[1];
        for (int i = 2; i < size; ++i) {
            if (maxCurr > 0) {
                maxCurr += prices[i];
            } else {
                maxCurr = prices[i];
            }
            maxTotal = max(maxTotal, maxCurr);
        }

        if (maxTotal < 0) {
            maxTotal = 0;
        }

        return maxTotal;
    }
private:
    inline int max(int a, int b) {
        return a > b ? a : b;
    }
};

