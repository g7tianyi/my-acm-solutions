/*
 ID: fairyroad1106
 LANG: C++
 TASK: pprime
 */
#include <cstdio>
#include <cmath>

#ifdef LOCAL_MODE
#define PROGID "input"
#else
#define PROGID "pprime"
#endif
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

int number[10] = { 0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
        100000000 };
int primes[10000] = { 2 }, primeCount = 1;

inline int length(int num) {
    int result = 1;
    while (num / 10) {
        ++result;
        num /= 10;
    }
    return result;
}

inline int getPalindrome(int half) {
    int lenh = length(half);
    int res = half * number[lenh];
    int len = lenh - 1;
    while (len) {
        res += (half / number[len + 1]) * number[lenh - len];
        half %= number[len + 1];
        --len;
    }
    return res;
}

void getPrimes() {
    for (int i = 3; i < 10001; ++i) {
        bool flag = true;
        double d = sqrt((double) i);
        for (int j = 2; j <= d; j++) {
            if (i % j == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            primes[primeCount++] = i;
        }
    }
}

inline bool isPrime(int num) {
    if (num == 1)
        return false;
    for (int i = 0; i < primeCount && primes[i] < num; ++i)
        if (num % primes[i] == 0 && num != primes[i])
            return false;
    return true;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int a, b;
    scanf("%d %d", &a, &b);
    getPrimes();

    int lena = length(a), lenb = length(b);
    int i, j, tmp;
    for (i = lena; i < lenb + 1; ++i) { // generate palindrome with length i
        if (i & 0x1u) { // odd
            j = number[(i + 1) / 2];
            for (; j < number[(i + 1) / 2 + 1]; ++j) {
                if (!(j / number[length(j)] & 0x1u))
                    continue;
                tmp = getPalindrome(j);
                if (tmp > b) {
                    return 0;
                }
                if (tmp >= a && isPrime(tmp)) {
                    printf("%d\n", tmp);
                }
            }
        } else if (i == 2) {
            printf("11\n");
        }
    }
    return 0;
}

