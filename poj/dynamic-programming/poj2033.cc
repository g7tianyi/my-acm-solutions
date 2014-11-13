/**
 * http://poj.org/problem?id=2033
 * DP
 */

#include <cstdio>
#include <cstring>

const int MAX_LEN = 1 << 16;

char buf[MAX_LEN];
long dp[MAX_LEN];

int main() {
    while (scanf("%s", buf) != EOF) {
        if (strcmp(buf, "0") == 0) {
            break;
        }

        int len = strlen(buf);

        // dp[i] is the maximum decoding solutions ending in i
        // (the input string guarantee all digits are valid)
        // if buf[i] == '0', i > 1 ? dp[i - 2] : 1
        // else
        //   1) view buf[i] as a single encoded letter, i.e., 'A' - 'J'
        //   2) view buf[i - 1, i]'s combination as a encoded letter 'K' - 'Z'
        dp[0] = 1;
        for (int i = 1, num; i < len; ++i) {
            if (buf[i] == '0') {
                // 10...
                // 12720...
                dp[i] = (i > 1 ? dp[i - 2] : 1);
            } else {
                // 1342...
                dp[i] = dp[i - 1]; // being a char alone
                // 1322, also, can be viewed as a char together with the previous digit
                // or, buf[i - 1] != '0' &&
                //        (buf[i - 1] - '0' >= 0 && buf[i - 1] - '0' < 3
                //           && buf[i] - '0' >= 0 && buf[i] - '0' < 7)
                num = (buf[i - 1] - '0') * 10 + (buf[i] - '0');
                if (num > 10 && num <= 26) {
                    dp[i] += (i > 1 ? dp[i - 2] : 1);
                }
            }
        }

        printf("%ld\n", dp[len - 1]);
    }

    return 0;
}

