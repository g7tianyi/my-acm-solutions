/**
 * ZOJ 1086, Octal Fractions
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXSIZE = 100;

int main() {
    char input[MAXSIZE], ans[MAXSIZE];
    int len, i, j, index, num, temp;

    while (scanf("%s", input) != EOF) {
        len = strlen(input);
        memset(ans, 0, sizeof(ans));
        index = 0;
        for (i = len - 1; i > 1; i--) {
            num = input[i] - '0';
            for (j = 0; j < index || num; j++) {
                temp = num * 10 + (j < index ? ans[j] - '0' : 0); // add the carry number
                ans[j] = temp / 8 + '0';
                num = temp % 8;
            }
            index = j;
        }
        ans[j] = '\0';
        printf("%s [8] = 0.%s [10]\n", input, ans);
    }

    return 0;
}

