/**
 * http://acm.timus.ru/problem.aspx?space=1&num=1005
 * 0-1 packing problem costs too much space
 * considering that there is only up to 20 numbers,
 * I suppose DFS is the better choice
 */
#include <cstdio>

int N, all, half, result;
int value[24];

inline int abs(int a) {
    return a > 0 ? a : -a;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

void DFS(int currsum, int depth) {
    if (depth > N) {
        if (abs(currsum - half) < abs(result - half)) {
            result = currsum;
        }
        return;
    }
    DFS(currsum + value[depth], depth + 1);
    DFS(currsum, depth + 1);
}

int main() {
    scanf("%d", &N);
    all = 0, result = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &value[i]);
        all += value[i];
    }
    half = (all >> 1);
    DFS(0, 0);
    result <<= 1;
    printf("%d\n", abs(all - result));
    return 0;
}

