/**
 * http://poj.org/problem?id=1326
 * Mileage Bank
 */

#include <iostream>

char buf[128];
int miles[3];

int main() {
    memset(miles, 0, sizeof(miles));
    while (fgets(buf, sizeof(buf), stdin) != NULL
            && strcmp(buf, "#\n") != 0) {

        if (strcmp(buf, "0\n") == 0) {
            // end of a case
            int result = 0;
            for (int i = 0; i < 3; ++i) {
                result += miles[i];
            }
            printf("%d\n", result);
            memset(miles, 0, sizeof(miles));
        } else {
            char* pch = strtok(buf, " \t");
            pch = strtok(NULL, " \t");
            pch = strtok(NULL, " \t");
            int mile = atoi(pch);
            pch = strtok(NULL, " \t");
            char type = *pch;

            if (type == 'F') {
                miles[0] += (mile << 1);
            } else if (type == 'B') {
                miles[1] += (mile + ((mile + 1) >> 1));
            } else {
                mile = mile < 500 ? 500 : mile;
                miles[2] += mile;
            }
        }
    }

    return 0;
}

