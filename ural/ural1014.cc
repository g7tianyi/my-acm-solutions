/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1014
 * Greedy algorithm
 */
#include <cstdio>
#include <cstring>

int main() {
    int num;
    scanf("%d", &num);
    if (num == 0) {
        printf("10\n");
    } else if (num < 10) {
        printf("%d\n", num);
    } else {
        int res[10], j = 0;
        memset(res, 0, sizeof(res));
        for (int i = 9; i > 1;) {
            if (num % i == 0) {
                num /= i, res[j++] = i;
            } else {
                --i;
            }
        }
        if (num != 1) {
            printf("-1\n");
        } else {
            for (int i = j - 1; i >= 0; --i) {
                printf("%d", res[i]);
            }
        }
    }

    return 0;
}

