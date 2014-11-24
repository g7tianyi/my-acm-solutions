/**
 * http://poj.org/problem?id=2405
 */

#include <iostream>
#include <cmath>

const double PI = acos(-1.0);

/**
 * volume of the whole cylinder: V0 = pi * (D/2)^2 * D
 * volume of the small cylinder: V1 = pi * (d/2)^2 * d
 * volume of the frustums:       V2 = 1/3 * pi * [ (D/2)^2 * (D/2) - (d/2)^2 * (d/2)]
 * V = V0 - (V1 + 2 * V2)
 */
int main() {
    int D, V;
    double d;
    while (scanf("%d %d", &D, &V) != EOF && D && V) {
        d = pow(D * D * D - (6 * V / PI), 1.0 / 3.0);
        printf("%.3f\n", d);
    }
    return 0;
}

