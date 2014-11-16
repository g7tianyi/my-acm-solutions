/**
 * http://poj.org/problem?id=3006
 */

#include <iostream>

typedef unsigned long long ullong;
const ullong MAX = 1000005;
bool prime[MAX];

int main() {
    // http://www.csie.ntnu.edu.tw/~u91029/Prime.html
    // get all prime numbers less than MAX
    memset(prime, true, sizeof(prime));
    prime[0] = false, prime[1] = false;
    for (ullong i = 2; i < MAX; ++i) {
        if (prime[i]) {
            // 欲刪掉質數 i 的倍數之時，早已刪掉 1 倍到 i-1 倍了，直接從 i 倍開始。
            for (ullong j = i * i; j < MAX; j += i) {
                prime[j] = false;
            }
        }
    }

    int first, delta, count;
    while (scanf("%d %d %d", &first, &delta, &count) != EOF
            && (first || delta || count)) {
        while (count) {
            if (prime[first]) {
                --count;
            }
            first += delta;
        }
        printf("%d\n", first - delta);
    }
    return 0;
}

