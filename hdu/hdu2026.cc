
/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2026
 */
#include <cstdio>
#include <cstring>

char buffer[105];

int main() {
    int i, len;
    while (gets(buffer)) {
        if (buffer[0] != ' ')
            buffer[0] -= 32;
        len = strlen(buffer);
        for (i = 1; i < len; i++) {
            if (buffer[i] != ' ' && buffer[i - 1] == ' ')
                buffer[i] -= 32;
        }
        puts(buffer);
    }
    return 0;
}

