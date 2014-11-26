/**
 * http://poj.org/problem?id=1068
 * Parencodings
 */

#include <iostream>
#include <stack>

std::stack<int> stack;
char buf[256];
int  dp[256];

int main() {
    int T, len;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &len);
        int num, top = 0, k = 1;
        for (int i = 0; i < len; ++i) {
            scanf("%d", &num);
            for (int j = 0; j < num - top; ++j) {
                buf[k++] = '(';
            }
            buf[k++] = ')';
            top = num;
        }

        memset(dp, -1, sizeof(dp));
        for (int i = 1; i < k; ++i) {
            if (buf[i] == '(' ) {
                stack.push(i);
            } else {
                dp[i] = stack.top();
                stack.pop();
            }
        }

        for (int i = 1; i < k; ++i) {
            if (dp[i] > 0) { // a pos for right parenthesis
                printf("%d ", (i - dp[i] + 1) >> 1);
            }
        }
        printf("\n");
    }

    return 0;
}


