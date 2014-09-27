/*
 ID: fairyroad1106
 PROG: crypt1
 LANG: C++
 */
#include <cstdio>
#include <cstring>

#define PROGID "crypt1"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

bool flag[10];

inline bool valid(int num) {
    while (num) {
        if (!flag[num % 10]) {
            return false;
        }
        num /= 10;
    }
    return true;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int N, num;
    scanf("%d", &N);
    memset(flag, false, sizeof(flag));
    for (int i = 0; i < N; ++i) {
        scanf("%d", &num);
        flag[num] = true;
    }

    int result = 0;
    for (int i = 100; i < 1000; ++i) {
        if (!valid(i)) {
            continue;
        }
        for (int j = 10; j < 100 && i * j < 10000; ++j) {
            if (i * (j / 10) > 999 || i * (j % 10) > 999) {
                continue;
            }
            if (valid(j) && valid(i * j) && valid(i * (j / 10))
                    && valid(i * (j % 10))) {
                ++result;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}

