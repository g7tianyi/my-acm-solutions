#include <cstdio>

class Solution {
public:
    int singleNumber(int A[], int n) {
        int result = A[0];
        for (int i = 1; i < n; ++i) {
            result ^= A[i];
        }
        return result;
    }
};

Solution solution;

int main() {
    int arr1[11] = { 1, 4, 18, 11, 23, 18, 4, 23, 9, 11, 1 };
    int arr2[11] = { -1, -4, -18, -11, -23, -18, -4, -23, -9, -11, -1 };
    int arr3[11] = { -1, -4, -18, -11, -23, 0, -18, -4, -23, -11, -1 };
    int arr4[1]  = { 1 };
    int arr5[1]  = { 0 };

    printf("%d\n", solution.singleNumber(arr1, 11));
    printf("%d\n", solution.singleNumber(arr2, 11));
    printf("%d\n", solution.singleNumber(arr3, 11));
    printf("%d\n", solution.singleNumber(arr4, 1));
    printf("%d\n", solution.singleNumber(arr5, 1));

    return 0;
}

