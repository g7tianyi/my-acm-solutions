#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        for (int i = 0; i < gas.size(); ) {
            int left = 0, j = 0;
            for (; j < gas.size(); j++) {
                int pos = (i + j) % gas.size();
                left = left + gas[pos] - cost[pos];
                if (left < 0) {
                    break;
                }
            }
            if (j == gas.size()) {
                return i;
            } else {
                i += (j + 1);
            }
        }
        return -1;
    }
};

Solution solu;

int main() {


    return 0;
}

