/**
 * http://poj.org/problem?id=3094
 */

#include <iostream>

char buf[260];

int main() {
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (buf[0] == '#') {
            break;
        }
        int len = strlen(buf), sum = 0;
        for (int i = 0; i < len; ++i) {
            if (buf[i] < 'A' || buf[i] > 'Z') {
                continue;
            }
            sum += (i + 1) * (buf[i] - 'A' + 1);
        }
        printf("%d\n", sum);
    }
    return 0;
}

