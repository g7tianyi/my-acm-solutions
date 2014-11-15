/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2018
 */

#include <iostream>

int cow[64];

int main() {
    int N;
    cow[0] = 1, cow[1] = 2, cow[2] = 3;
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 3; i < N; ++i) {
            // cow[i-1] is the cows from yesterday
            // cow[i-3] is the new born cows
            cow[i] = cow[i - 1] + cow[i - 3];
        }
        printf("%d\n", cow[N - 1]);
    }
    return 0;
}

