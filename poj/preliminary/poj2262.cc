#include <iostream>

typedef unsigned long long ullong;
const ullong MAX = 1000005;
bool is_prime[MAX];
int prime[MAX];

int main() {
    // http://www.csie.ntnu.edu.tw/~u91029/Prime.html
    // get all prime numbers less than MAX
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false, is_prime[1] = false;
    for (ullong i = 2; i < MAX; ++i) {
        if (is_prime[i]) {
            // 欲刪掉質數 i 的倍數之時，早已刪掉 1 倍到 i-1 倍了，直接從 i 倍開始。
            for (ullong j = i * i; j < MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2, j = 0; i < MAX; ++i) {
        if (is_prime[i]) {
            prime[j++] = i;
        }
    }

    int num;
    while (scanf("%d", &num) != EOF && num) {
        int resa = -1, resb = -1;
        for (int i = 0; prime[i] <= (num >> 1); ++i) {
            if (is_prime[num - prime[i]]) {
                if (resa == -1) {
                    resa = prime[i], resb = num - prime[i];
                    break;
                }
            }
        }
        if (resa == -1) {
            printf("Goldbach's conjecture is wrong.\n");
        } else {
            printf("%d = %d + %d\n", num, resa, resb);
        }
    }
    return 0;
}

