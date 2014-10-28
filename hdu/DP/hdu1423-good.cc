/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1423
 *
 * Greatest Common Increasing Subsequence
 */

#include <cstdio>
#include <cstring>

const int MAX_ELEM = 501;
int arr1[MAX_ELEM], arr2[MAX_ELEM];
int dp[2][MAX_ELEM];

int main() {
    int cases;
    scanf("%d", &cases);
    int num1, num2;
    while (cases--) {
        scanf("%d", &num1);
        for (int i = 0; i < num1; ++i) {
            scanf("%d", &arr1[i]);
        }
        scanf("%d", &num2);
        for (int i = 0; i < num2; ++i) {
            scanf("%d", &arr2[i]);
        }

        memset(dp, 0, sizeof(dp));
        int result = 0, premax;
        int curr = 1, prev = 0;
        for (int i = 0; i < num1; ++i) {
            premax = 0;
            for (int j = 0; j < num2; ++j) {
                dp[curr][j] = dp[prev][j];
                if (arr1[i] > arr2[j] && premax < dp[prev][j]) {
                    // next time when we found a j' meets arr1[i] == arr2[j']
                    // the j can be an option for j' to get the longest common increasing subsequence
                    // since we have arr2[j'] == arr1[i] > arr2[j]
                    // nice optimization
                    premax = dp[prev][j]; // dp[i-1][j]
                }
                if (arr1[i] == arr2[j]) {
                    dp[curr][j] = premax + 1;
                }
                if (result < dp[curr][j]) {
                    result = dp[curr][j];
                }
            }
            curr ^= 1, prev ^= 1;
        }
        printf("%d\n", result);
        if (cases) {
            printf("\n");
        }
    }
    return 0;
}

