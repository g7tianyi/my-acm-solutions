/**
 * http://poj.org/problem?id=2105
 * IP Address
 */

#include <iostream>

char buf[36];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", buf);
        int num = 0;
        for (int i = 0; i < 32; ++i) {
            num <<= 1;
            num += (buf[i] == '1');
            if ((i + 1) % 8 == 0) {
                printf("%d", num);
                num = 0;
                if (i != 31) {
                    printf(".");
                } else {
                    printf("\n");
                }
            }
        }
    }
    return 0;
}

