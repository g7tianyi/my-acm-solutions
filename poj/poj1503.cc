/**
 * http://poj.org/problem?id=1503
 *
 * Big number addtion.
 */

#include <cstdio>
#include <cstring>

char nums[105];
int sums[105];

inline void swap(char& a, char& b) {
    char t = a;
    a = b;
    b = t;
}

int main() {
    int maxlen = -1;
    memset(sums, 0, sizeof(sums));
    while (scanf("%s", nums) != EOF) {
        int len = strlen(nums);
        if (len == 1 && nums[0] == '0') {
            break;
        }
        if (maxlen < len) {
            maxlen = len;
        }
        // reverse
        int i = 0, j = len - 1;
        while (i < j) {
            swap(nums[i++], nums[j--]);
        }

        for (i = 0; i < len; ++i) {
            sums[i] += (nums[i] - '0');
        }
    }

    for (int i = 0; i < maxlen; ++i) {
        sums[i + 1] += sums[i] / 10;
        sums[i] %= 10;
    }

    int i = maxlen - (sums[maxlen] == 0);
    for (; i >= 0; --i) {
        printf("%d", sums[i]);
    }
    printf("\n");

    return 0;
}

