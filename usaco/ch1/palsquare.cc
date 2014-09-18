/*
 ID: fairyroad1106
 PROG: palsquare
 LANG: C++
 */
#include <cstdio>
#include <cstring>

#define PROGID "palsquare"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

enum BASE_TYPE {
    SOURCE = 0,
    SQUARE = 1
};

char map[21] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K' };
char buffer[2][20];

void kbase(int num, int base, BASE_TYPE base_type) {
    int i = 0;
    while (num) {
        buffer[base_type][i++] = map[num % base];
        num /= base;
    }
}

bool palindromic() {
    int start = 0, end = strlen(buffer[SQUARE]) - 1;
    while (start < end) {
        if (buffer[SQUARE][start++] != buffer[SQUARE][end--]) {
            return false;
        }
    }
    return true;
}

void reverse() {
    int start = 0, end = strlen(buffer[SOURCE]) - 1;
    char ch;
    while (start < end) {
        ch = buffer[SOURCE][start];
        buffer[SOURCE][start] = buffer[SOURCE][end];
        buffer[SOURCE][end] = ch;
        ++start;
        --end;
    }
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int N;
    scanf("%d", &N);

    for (int i = 1, j; i < 301; ++i) {
        j = i * i;
        memset(buffer, 0, sizeof(buffer));
        kbase(j, N, SQUARE);
        if (palindromic()) {
            kbase(i, N, SOURCE);
            reverse();
            printf("%s %s\n", buffer[SOURCE], buffer[SQUARE]);
        }
    }

    return 0;
}

