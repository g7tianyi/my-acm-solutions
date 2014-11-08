#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

static const int MAX_LEN = 10001;

char buf[MAX_LEN];

inline int _abs(int a) {
    return a > 0 ? a : -a;
}

int main() {
    int case_num = 0;
    scanf("%d", &case_num);
    while (case_num--) {
        scanf("%s", buf);
        int result = 0;
        int former = 0, latter = strlen(buf) - 1;
        while (former < latter) {
            result += _abs(buf[former++] - buf[latter--]);
        }
        printf("%d\n", result);
    }
    return 0;
}

