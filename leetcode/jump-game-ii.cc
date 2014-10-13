#include <algorithm>
#include <iostream>

class Solution {
public:
    int jump(int array[], int size) {
        int result = 0;
        // currdis, curr distance which can be reached in result steps
        // farthest, farthest distance can be reached by result + 1 steps
        int currdis = 0, farthest = 0;
        for (int i = 0; i < size; ++i) {
            if (i > currdis) {
                currdis = farthest;
                ++result;
            }
            farthest = std::max(farthest, i + array[i]);
        }
        return result;
    }
};

Solution solu;

int main() {
    int array[] = { 2, 3, 1, 1, 4 };
    std::cout << solu.jump(array, 5) << std::endl;
    return 0;
}

