#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int key) {
        if (nums.empty()) {
            return 0;
        }
        size_t size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        if (size == 2) {
            return nums[0] + nums[1];
        }

        size_t i, j, k;
        int subres, curres, result = nums[0] + nums[1] + nums[2] - key;
        for (i = 0; i < size; ++i) {
            for (j = i + 1; j < size; ++j) {
                subres = nums[i] + nums[j] - key;
                for (k = j + 1; k < size; ++k) {
                    curres = subres + nums[k];
                    if (std::abs(result) > std::abs(curres)) {
                        result = curres;
                    }
                }
            }
        }

        return result + key;
    }
};
Solution sol;

int main() {

    vector<int> S;
    S.push_back(-1);
    S.push_back(2);
    S.push_back(1);
    S.push_back(-4);

    std::cout << sol.threeSumClosest(S, 1) << std::endl;

    return 0;
}

