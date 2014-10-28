/**
 * http://poj.org/problem?id=2127
 *
 * Greatest Common Increasing Subsequence
 */

#include <cstdio>
#include <cstring>

const int MAX_ELEM = 501;

int arr1[MAX_ELEM];
int arr2[MAX_ELEM];
int dp[MAX_ELEM][MAX_ELEM];
int path[MAX_ELEM][MAX_ELEM];
int route[MAX_ELEM];

int main() {
    int num1, num2;
    scanf("%d", &num1);
    for (int i = 0; i < num1; ++i) {
        scanf("%d", &arr1[i]);
    }
    scanf("%d", &num2);
    for (int i = 0; i < num2; ++i) {
        scanf("%d", &arr2[i]);
    }

    memset(dp, 0, sizeof(dp));
    memset(path, -1, sizeof(path));
    int result = 0, resi, resj;
    int premax, prej;
    for (int i = 0; i < num1; ++i) {
        premax = 0;
        for (int j = 0; j < num2; ++j) {
            dp[i][j] = i > 0 ? dp[i - 1][j] : 0;
            if (arr1[i] > arr2[j] && premax < dp[i - 1][j]) {
                // next time when we found a j' meets arr1[i] == arr2[j']
                // the j can be an option for j' to get the longest common increasing subsequence
                // since we have arr2[j'] == arr1[i] > arr2[j]
                // nice optimization
                premax = i > 0 ? dp[i - 1][j] : 0; // dp[i-1][j]
                prej = j;
            }
            if (arr1[i] == arr2[j]) {
                dp[i][j] = premax + 1;
                path[i][j] = prej;
            }
            if (result < dp[i][j]) {
                result = dp[i][j];
                resi = i, resj = j;
            }
        }
    }
    printf("%d\n", result);

    int len = result - 1;
    if (result > 0) { // edge case, watch out
        route[len--] = resj;
    }
    while (len >= 0 && resi >= 0 && resj >= 0) {
        if (path[resi][resj] >= 0) {
            route[len--] = path[resi][resj];
            resj = path[resi][resj];
        }
        --resi;
    }
    for (int i = 0; i < result; ++i) {
        printf("%d ", arr2[route[i]]);
    }
    printf("\n");

    return 0;
}

