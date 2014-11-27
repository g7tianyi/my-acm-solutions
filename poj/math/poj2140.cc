/**
 * http://poj.org/problem?id=2140
 * Herd Sums
 */

#include <iostream>

// suppose sequence { a, a + 1, a + 2,..., a + k }
// is the one we're looking for, we have
// num = (k + 1) * a + k * (k + 1) / 2
//     = (k + 1) * (a + k / 2)
// we can see k must be a even number <= k / 2
// so k + 1 is an odd number
// then the number of odd factor is the result
int main() {
    int num, result = 0;
    scanf("%d", &num);
    for (int i = 1; i <= num; i += 2) {
        if (num % i == 0) {
            ++result;
        }
    }
    printf("%d\n", result);
    return 0;
}

