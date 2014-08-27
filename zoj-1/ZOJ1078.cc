/**
 * ZOJ 1078, Palindrom Numbers
 */
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char buffer[32];
bool flag[20];

// note: if you want to get the presentation in scale for num
// you will need to reverse the buffer from 0 to returned pos
int convert(int num, int scale) {
    memset(buffer, 0, sizeof(buffer));
    int pos = 0, res;
    while (num) {
        res = num % scale;
        if (res < 10) {
            buffer[pos] = res + '0';
        } else {
            buffer[pos] = res + 'A';
        }
        num /= scale;
        ++pos;
    }
    return pos - 1;
}

bool is_palindrom(int start, int end) {
    while (start <= end) {
        if (buffer[start] != buffer[end]) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}

int main() {
    int num;
    while (scanf("%d", &num) != EOF && num) {
        memset(flag, 0, sizeof(flag));
        bool found = false;
        for (int i = 2; i <= 16; ++i) {
            if (is_palindrom(0, convert(num, i))) {
                flag[i] = true;
                found = true;
            }
        }
        if (found) {
            printf("Number %d is palindrom in basis", num);
            for (int i = 2; i <= 16; ++i) {
                if (flag[i]) {
                    printf(" %d", i);
                }
            }
            printf("\n");
        } else {
            printf("Number %d is not a palindrom\n", num);
        }
    }
    return 0;
}

