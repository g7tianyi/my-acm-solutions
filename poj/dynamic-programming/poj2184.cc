/**
 * http://poj.org/problem?id=2184
 * Cow Exhibition
 *
 * dynamic programming.
 * 0-1 packing problem. only the capacity could be negative, interesting and be care
 */

#include <iostream>

enum {
    MAX_COW =  105,
    MAX_FAC =  200000, // 2 * 100 * 1000
    MIN_INF = -2000000000
};

enum Type {
    SMART,
    FUNNY,
};

int cow[MAX_COW][2];
int dp[MAX_FAC + 2];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &cow[i][SMART], &cow[i][FUNNY]);
    }

    int pivot = MAX_FAC >> 1;
    // dp[i][j], the maximum smart score picking from
    // the former i cows when the funny score is j
    memset(dp, 0x88, sizeof(dp)); // 0x88 => 10001000, each int must be a negative number
    dp[pivot] = 0;

    for (int i = 0; i < N; ++i) {
        if (cow[i][FUNNY] > 0) {
            for (int j = MAX_FAC; j >= cow[i][FUNNY]; --j) {
                dp[j] = std::max(dp[j], dp[j - cow[i][FUNNY]] + cow[i][SMART]);
            }
        } else {
            for (int j = 0; j - cow[i][FUNNY] <= MAX_FAC; ++j) {
                dp[j] = std::max(dp[j], dp[j - cow[i][FUNNY]] + cow[i][SMART]);
            }
        }
    }

    int result = 0;
    for (int i = pivot; i <= MAX_FAC; ++i) {
        if (dp[i] >= 0 && result < dp[i] + i - pivot) {
            result = dp[i] + i - pivot; // i - pviot is the sum of funny score
        }
    }

    printf("%d\n", result);

    return 0;
}

