#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    int findMin(vector<int>& num) {
        int size = num.size();
        int first = 0, last = size - 1, mid;
        while (first < last) {
            mid = first + ((last - first) >> 1);
            if (num[mid] > num[last]) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        return num[last];
    }
};

Solution solu;

int array1[7] = { 4, 5, 6, 7, 0, 1, 2 };
int array2[7] = { 7, 0, 1, 2, 4, 5, 6 };
int array3[8] = { 7, 8, 0, 1, 2, 4, 5, 6 };
int array4[8] = { 8, 0, 1, 2, 4, 5, 6, 7 };
int array5[8] = { 4, 5, 6, 7, 8, 0, 1, 2 };
int array6[1] = { 2 };
int array7[2] = { 4, 2 };
int array8[3] = { 4, 2, 3 };

vector<int> nums;

void fillVector(int array[], int len) {
    nums.clear();
    for (int i = 0; i < len; ++i) {
        nums.push_back(array[i]);
    }
}

int main() {
    fillVector(array1, 7);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array2, 7);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array3, 8);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array4, 8);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array5, 8);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array6, 1);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array7, 2);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array8, 3);
    std::cout << solu.findMin(nums) << std::endl;

    return 0;
}

