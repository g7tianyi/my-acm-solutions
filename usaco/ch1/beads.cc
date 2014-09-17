/*
 ID: fairyroad1106
 PROG: beads
 LANG: C++
 */
#include <cstdio>

#define PROGID "beads"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

#define ABS(a) ((a) > 0 ? (a) : -(a))
#define EQUALS(ch1, ch2) (ch1 == ch2 || ch1 == 'w' || ch2 == 'w')

const int MAX_LENGTH = 360;

int len;
char buf[MAX_LENGTH];

/**
 * pitfalls
 * 1) if matching starts from 'w', once encoutering
 *    a non-'w' characer ch, should match ch later,
 *    and this is why DP is not very applicable
 * 2) matching may overlap
 */
int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    scanf("%d\n", &len);
    scanf("%s", buf);

    char cur; // current character
    int i, j, left, leftmost, right, result = -1;
    for (i = 0; i < len; ++i) {
        cur = buf[i];
        j = i - 1, left = 1;
        while (ABS(i - j) < len
                && EQUALS(buf[(j + len) % len], cur)) {
            leftmost = (j + len) % len;
            if (cur == 'w' && buf[(j + len) % len] != 'w') {
                cur = buf[(j + len) % len];
            }
            --j; ++left;
        }

        if (leftmost == i + 1) {
            result = len;
            break;
        }

        cur = buf[i + 1];
        j = i + 2, right = 1;
        while ((j % len) != leftmost
                && EQUALS(buf[j % len], cur)) {
            if (cur == 'w' && buf[j % len] != 'w') {
                cur = buf[j % len];
            }
            ++j; ++right;
        }

        if (result < left + right) {
            result = left + right;
        }
    }

    printf("%d\n", result);
    return 0;
}

