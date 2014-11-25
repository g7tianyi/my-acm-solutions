/**
 * http://poj.org/problem?id=2381
 * Random Gap
 */

#include <iostream>
#include <limits>

const int MAX = 16000001;
const long long MIN = std::numeric_limits<long long>::min();

bool visit[MAX];

int main() {
    long long a, c, m, r0;
    scanf("%lld %lld %lld %lld", &a, &c, &m, &r0);
    memset(visit, false, sizeof(visit));
    visit[r0] = true;
    long long r1, result = MIN;
    while (true) {
        r1 = ( (a % m) * (r0 % m) + c) % m;
        // there are no other Rk that Ri ≤ Rk ≤ Rj
        // the difference Rj − Ri is maximal
        // ... Faint...
        if (result < r1 - r0) {
            result = r1 - r0;
        }
        if (visit[r1]) {
            break;
        }
        visit[r1] = true;
        r0 = r1;
    }
    printf("%lld\n", result);
    return 0;
}

