/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2017
 *
 * KMP
 */

#include <iostream>

char buf[1024];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", buf);
        int len = strlen(buf), count = 0;
        for (int i = 0; i < len; ++i) {
            if (buf[i] >= '0' && buf[i] <= '9') {
                ++count;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}

