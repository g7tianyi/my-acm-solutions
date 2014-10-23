#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int findMin(vector<int> &num) {
        int size = num.size();
        int first = 0, last = size - 1, mid;
        while (first < last) {
            mid = first + ((last - first) >> 1);
            // 1) we are searching the minimum
            // 2) we know that range [first, povit) are sorted
            // 3) so when num[mid] > num[last],
            //    we know range[first, mid] are all larger than num[last]
            if (num[mid] > num[last]) {
                first = mid + 1;
            } else if (num[mid] < num[last]) {
                // don't eliminate mid, we are seaching the minimum ^_^
                last = mid;
            } else {
                // check the test case below to see why
                --last;
            }
        }
        return num[last];
    }
};

Solution solu;

int array1[7] = { 4, 5, 5, 5, -1, 1, 2 };
int array2[7] = { 7, -2, 1, 2, 2, 2, 2 };
int array3[8] = { 3, 3, 3, 3, 3, 3, -3, 2 };
int array4[8] = { 3, -4, 2, 3, 3, 3, 3, 3 };
int array5[1] = { 2 };
int array6[2] = { 4, 2 };
int array7[3] = { 4, 2, 2 };

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

    fillVector(array5, 1);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array6, 2);
    std::cout << solu.findMin(nums) << std::endl;

    fillVector(array7, 3);
    std::cout << solu.findMin(nums) << std::endl;

    return 0;
}

