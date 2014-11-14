/**
 * http://poj.org/problem?id=3981
 *
 * string
 */

#include <iostream>
#include <cstring>

char buf[1024];

int main() {
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        int i = 0, len = strlen(buf);
        while (i < len) {
            if (i + 2 < len && buf[i] == 'y'
                    && buf[i + 1] == 'o' && buf[i + 2] == 'u') {
                printf("we");
                i += 3;
            } else {
                printf("%c", buf[i++]);
            }
        }
    }
    return 0;
}

