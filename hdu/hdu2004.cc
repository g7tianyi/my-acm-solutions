/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2004
 */
#include <cstdio>

int main() {
    int score;
    while(scanf("%d", &score) != EOF) {
        if (score < 0 || score > 100) {
            printf("Score is error!");
        } else if (score >= 90) {
            printf("A");
        } else if (score >= 80) {
            printf("B");
        } else if (score >= 70) {
            printf("C");
        } else if (score >= 60) {
            printf("D");
        } else {
            printf("E");
        }
        printf("\n");
    }
    return 0;
}

