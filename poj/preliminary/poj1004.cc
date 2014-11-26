/**
 * http://poj.org/problem?id=1004
 * Financial Management
 */

#include <iostream>

int main() {
    double cost, total = 0.0;
    for (int i = 0; i < 12; ++i) {
        scanf("%lf", &cost);
        total += cost;
    }
    printf("$%.2lf\n", total / 12);
    return 0;
}

