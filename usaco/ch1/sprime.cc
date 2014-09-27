/*
 ID: fairyroad1106
 LANG: C++
 TASK: sprime
 */
#include <cstdio>
#include <cmath>

#ifdef LOCAL_MODE
#define PROGID "usaco"
#else
#define PROGID "sprime"
#endif
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

// the first position can only be 2 3 5 7
// prime number with only one digit can only be 2 3 5 7
// others can only be 1 3 7 9, since all prime numbers
// can only end with one of them
int option[2][4] = { { 2, 3, 5, 7 }, { 1, 3, 7, 9 } };
int N;

inline bool isPrime(int num) {
    if (num < 2) {
        return false;
    }
    double d = sqrt(num);
    for (int j = 2; j <= d; j++) {
        if (num % j == 0) {
            return false;
        }
    }
    return true;
}

void sprime(int n, int num) {
    if (n == N) {
        printf("%d\n", num);
        return;
    }
    for (int i = 0, tmp; i < 4; ++i) {
        tmp = num * 10 + option[!!n][i];
        if (isPrime(tmp)) {
            sprime(n + 1, tmp);
        }
    }
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);
    scanf("%d\n", &N);
    sprime(0, 0);
    return 0;
}

