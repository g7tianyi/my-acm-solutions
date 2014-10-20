#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    double findMedianSortedArrays(int arr1[], int len1, int arr2[], int len2) {
        int len = len1 + len2;
        if (len & 0x1u) {
            return findKthElem(arr1, len1, arr2, len2, (len >> 1) + 1);
        } else {
            return (findKthElem(arr1, len1, arr2, len2, len >> 1)
                    + findKthElem(arr1, len1, arr2, len2, (len >> 1) + 1)) >> 1;
        }
    }
private:
    double findKthElem(int arr1[], int len1, int arr2[], int len2, int k) {
        if (len1 > len2) {
            return findKthElem(arr2, len2, arr1, len1, k);
        }
        if (len1 == 0) {
            return arr2[k - 1];
        }
        if (k == 1) {
            return std::min(arr1[0], arr2[0]);
        }

        int kArr1 = std::min(k >> 1, len1), kArr2 = k - kArr1;
        if (arr1[kArr1 - 1] < arr2[kArr2 - 1]) {
            return findKthElem(arr1 + kArr1, len1 - kArr1, arr2, len2,
                    k - kArr1);
        }
        if (arr1[kArr1 - 1] > arr2[kArr2 - 1]) {
            return findKthElem(arr1, len1, arr2 + kArr2, len2 - kArr2,
                    k - kArr2);
        }
        return arr1[kArr1 - 1];
    }
};

Solution solu;

