#include <algorithm>
#include <iostream>

#include <vector>
using std::vector;

class Solution {
public:
    typedef long long LONG;

    int largestRectangleArea(vector<int>& height) {
        int size = height.size();
        if (size == 0) {
            return 0;
        }

        vector<int> left(size), right(size);
        for (int i = 0; i < size; ++i) {
            left[i] = i, right[i] = i;
        }

        for (int i = 0; i < size; i++) {
            // height:  1  3  1  6  7  1  5  2  7
            // left' :  0  1  2  3  4  5  6  7  8
            // left  :  0  1  0  3  4  0  6  6  8
            while (left[i] > 0 && height[left[i] - 1] >= height[i]) {
                left[i] = left[left[i] - 1];
            }
        }

        for (int i = size - 1; i >= 0; i--) {
            // height:  1  3  1  6  7  1  5  2  7
            // right':  0  1  2  3  4  5  6  7  8
            // right :  8  1  8  4  4  8  6  8  8
            while (right[i] < size - 1 && height[right[i] + 1] >= height[i]) {
                right[i] = right[right[i] + 1];
            }
        }

        int result = 0, temp;
        for (int i = 0; i < size; i++) {
            temp = (right[i] - left[i] + 1) * height[i];
            if (temp > result) {
                result = temp;
            }
        }

        return result;
    }
};

Solution solu;


int main() {

    vector<int> V;
    V.push_back(1), V.push_back(3), V.push_back(1);
    V.push_back(6), V.push_back(7), V.push_back(1);
    V.push_back(5), V.push_back(2), V.push_back(7);
    std::cout << solu.largestRectangleArea(V) << std::endl;

    V.clear();
    V.push_back(10);
    std::cout << solu.largestRectangleArea(V) << std::endl;

    return 0;
}

