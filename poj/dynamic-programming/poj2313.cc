/**
 * http://poj.org/problem?id=2313
 *
 * greedy algo
 */

#include <iostream>

/**
 * Given b[i] = a[i] (1 <= i <= n) at the very begining, b[i] will have impact on 3
 * equations: |a[i]-b[i]| |b[i]-b[i-1]| |b[i]-b[i+1]|
 * and it is obviously that b[i] should be the median of a[i], b[i-1] and b[i+1]
 * put it on the number axis will find it very clear
 * before assign the median to b[i], it is in fact the median of b[i-1], b[i], b[i+1]
 *
 * Now we need to guarantee the propagation of updating b[i] is correct.
 *
 * We have
 *  - a[0] a[1] a[2] a[3] ... a[n]
 *  - b[0] b[1] b[2] b[3] ... b[n]
 *
 * b[1] = median(b[0], a[1], b[2]) (##)
 *
 * When figuring out the b[2] = median(b[1], a[2], b[3]) (**)
 * the b[1] could have 3 possibilities:
 *  1) b[1] = b[0], which means either of the followings:
 *     A) a[1] <= b[0] (b[1]) <= b[2]
 *     B) b[2] <= b[0] (b[1]) <= a[1]
 *     in A), equation (**) maybe:
 *        A') b[3] <= b[0] (b[1]) <= b[2]
 *        B') b[2] <= b[0] (b[1]) <= b[3]
 *     whichever the case is, equation (##) stands correct
 *
 *  ...The analysis can be applied to all cases...
 *
 */

int A[102], B[102];

inline int myabs(int a) {
    return a > 0 ? a : -a;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int median(int a, int b, int c) {
    int ma = max(a, max(b, c));
    int mi = min(a, min(b, c));
    return a ^ b ^ c ^ ma ^ mi;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }

    for (int i = 1; i < N - 1; ++i) {
        B[i] = median(B[i - 1], A[i], B[i + 1]);
    }

    int result = 0;
    for (int i = 0; i < N; ++i) {
        result += myabs(A[i] - B[i]);
    }

    for (int i = 0; i < N - 1; ++i) {
        result += myabs(B[i] - B[i + 1]);
    }

    printf("%d\n", result);
    return 0;
}

