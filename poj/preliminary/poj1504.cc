/**
 * http://poj.org/problem?id=1504
 * palindrome number/ reverse number. watching for some edge cases
 */

#include <iostream>

typedef long long llong;

const int FACTOR = 10;

// there maight be cases that 1000000003
// while reversed, the number will exceed INT_MAX
// so for security, we use long long
inline llong reverse(int num) {
    llong result = 0, tmp = static_cast<llong>(num);
    while (tmp) {
        result = result * FACTOR + tmp % FACTOR;
        tmp /= FACTOR;
    }
    return result;
}

int main() {
    int cases, num1, num2;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d %d", &num1, &num2);
        printf("%lld\n", reverse(reverse(num1) + reverse(num2)));
    }
    return 0;
}

