/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1423
 *
 * Greatest Common Increasing Subsequence
 */

#include <cstdio>
#include <cstring>

const int MAX_ELEM = 501;
int arr1[MAX_ELEM], arr2[MAX_ELEM];
int dp[MAX_ELEM];

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
        int result = 0;
        // O(N^3) algorithm, can be optimized
        for (int i = 0; i < num1; ++i) {
            for (int j = 0; j < num2; ++j) {
                if (arr1[i] == arr2[j]) {
                    dp[j] = 1;
                    for (int k = 0; k < j; ++k) {
                        if (arr2[k] < arr2[j] && dp[j] < dp[k] + 1) {
                            dp[j] = dp[k] + 1;
                        }
                    }
                }
                if (result < dp[j]) {
                    result = dp[j];
                }
            }
        }
        printf("%d\n", result);
        if (cases) {
            printf("\n");
        }
    }
    return 0;
}

