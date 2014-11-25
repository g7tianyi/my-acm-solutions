/**
 * http://poj.org/problem?id=2381
 * Random Gap
 */

#include <iostream>

const int MAX = 16000001;

bool appeared[MAX];

int main() {
    long long a, c, m, r;
    scanf("%lld %lld %lld %lld", &a, &c, &m, &r);
    memset(appeared, false, sizeof(appeared));
    appeared[r] = true;
    while (true) {
        r = ((a % m) * (r % m) + c) % m;
        if (appeared[r]) {
            break;
        }
        appeared[r] = true;
    }

    long long result = 0, prev = -1;
    for (long long curr = 0; curr < m; ++curr) {
        if (appeared[curr]) {
            if (prev >= 0 && result < curr - prev) {
                result = curr - prev;
            }
            prev = curr;
        }
    }

    printf("%lld\n", result);
    return 0;
}

