
/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1079
 */
#include <cstdio>

static int const MAX_LEN = 100000;
static int arr[MAX_LEN], res[MAX_LEN];

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    arr[0] = res[0] = 0;
    arr[1] = res[1] = 1;
    int currmax = 1;
    for (int i = 2, j; i < MAX_LEN; ++i) {
        j = i >> 1;
        if (i & 0x1u) {
            arr[i] = arr[j] + arr[j + 1];
        } else {
            arr[i] = arr[j];
        }
        currmax = max(currmax, arr[i]);
        res[i] = currmax;
    }

    int num;
    while (scanf("%d", &num) != EOF && num) {
        printf("%d\n", res[num]);
    }
    return 0;
}

