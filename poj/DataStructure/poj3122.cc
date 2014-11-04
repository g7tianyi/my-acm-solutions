/**
 * http://poj.org/problem?id=3122
 *
 * Pie
 *
 * binary seach. good.
 */

#include <cmath>
#include <cstdio>
#include <algorithm>

const int MAX_FRIEND = 10002;
const double PI = acos(-1.0);

int N, F; // num of pie and friend
double pie[MAX_FRIEND];

bool legal(double area) {
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += floor(pie[i] / area);
    }
    return sum >= F + 1;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d %d", &N, &F);
        double maxsize = 0;
        for (int i = 0, radius; i < N; ++i) {
            scanf("%d", &radius);
            pie[i] = PI * radius * radius;
            maxsize = std::max(maxsize, pie[i]);
        }

        double first = 0, last = maxsize, mid;
        while (last - first > 1e-5) {
            mid = (first + last) / 2;
            if (legal(mid)) {
                first = mid;
            } else {
                last = mid;
            }
        }

        printf("%.4lf\n", first);
    }
    return 0;
}

