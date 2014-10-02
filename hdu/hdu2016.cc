/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2016
 */
#include <cstdio>

int array[128];

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N) {
        int mindex = -1;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &array[i]);
            if (mindex == -1 || array[mindex] > array[i]) {
                mindex = i;
            }
        }
        int temp = array[mindex];
        array[mindex] = array[0];
        array[0] = temp;

        for (int i = 0; i < N - 1; ++i) {
            printf("%d ", array[i]);
        }
        printf("%d\n", array[N - 1]);
    }

    return 0;
}

