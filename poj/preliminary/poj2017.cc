/**
 * http://poj.org/problem?id=2017
 * Speed Limit
 */

#include <iostream>

int main() {
    int num;
    while (scanf("%d", &num) != EOF && num != -1) {
        int speed, currt, prevt = 0;
        int result = 0;
        while (num--) {
            scanf("%d %d", &speed, &currt);
            result += speed * (currt - prevt);
            prevt = currt;
        }
        printf("%d miles\n", result);
    }
    return 0;
}

