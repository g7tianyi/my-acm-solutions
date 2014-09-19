/*
 ID: fairyroad1106
 PROG: dualpal
 LANG: C++
 */
#include <cstdio>
#include <cstring>

#define PROGID "dualpal"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

char map[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char buf[40];

void kbase(int num, int base) {
    int i = 0;
    while (num) {
        buf[i++] = map[num % base];
        num /= base;
    }
}
bool palindromic() {
    int start = 0, end = strlen(buf) - 1;
    while (start < end) {
        if (buf[start++] != buf[end--]) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int num, start, count;
    scanf("%d %d", &num, &start);

    while (num) {
        ++start;
        count = 0;
        for (int base = 2; base <= 10; ++base) {
            memset(buf, 0, sizeof(buf));
            kbase(start, base);
            count += palindromic();
            if (count == 2) {
                printf("%d\n", start);
                --num;
                break;
            }
        }
    }

    return 0;
}

