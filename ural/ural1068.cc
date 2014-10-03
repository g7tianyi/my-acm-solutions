/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1068
 */
#include <cstdio>

inline int sum(int n) {
    return (n * (1 + n)) >> 1;
}

int main() {
    int num;
    scanf("%d", &num);
    if (num <= 0) {
        printf("%d\n", -1 * sum(-num) + 1);
    } else {
        printf("%d\n", sum(num));
    }
    return 0;
}

