/**
 * POJ 1690, (Your)((Term)((Project)))
 */
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_LENGTH = 260;
char buf[MAX_LENGTH];
char tmp[MAX_LENGTH];
bool red[MAX_LENGTH]; // redundant
int pair[MAX_LENGTH]; // pair of parentheses

int main() {
    int T;
    scanf("%d\n", &T);

    while (T--) {
        memset(buf, 0, sizeof(buf));
        fgets(buf, MAX_LENGTH, stdin);

        std::stack<int> paren;
        bool updated;
        int i, j, len;
        do {
            updated = false;

            j = 0, len = strlen(buf);
            memset(tmp, 0, sizeof(tmp));
            memset(pair, 0, sizeof(pair));
            for (i = 0; i < len; ++i) {
                if (buf[i] == ' ') {
                    continue;
                }
                if (buf[i] == '(') {
                    paren.push(j);
                } else if (buf[i] == ')') {
                    pair[paren.top()] = j;
                    pair[j] = paren.top();
                    paren.pop();
                }
                tmp[j++] = buf[i];
            }

            len = strlen(tmp);
            memset(red, 0, sizeof(red));
            for (i = 0; i < len; ++i) {
                if (tmp[i] == '('
                        && (i == 0 || tmp[i - 1] != '-' || abs(pair[i] - i) == 2)) { // This is the key code
                    red[i] = red[pair[i]] = true;
                    updated = true;
                }
            }

            memset(buf, 0, sizeof(buf));
            j = 0;
            for (i = 0; i < len; ++i) {
                if (red[i]) {
                    continue;
                }
                buf[j++] = tmp[i];
            }

        } while (updated);

        printf("%s", buf);
    }

    return 0;
}

