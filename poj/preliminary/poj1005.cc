#include <iostream>
#include <cmath>

const double PI = acos(-1.0);

int main() {
    int T;
    scanf("%d", &T);
    double x, y;
    for (int i = 1; i <= T; ++i) {
        scanf("%lf %lf", &x, &y);
        // (1 / 2) * (PI * R ^ 2)  = 50 * N
        // R ^ 2 = x ^ 2 + y ^ 2
        printf("Property %d: This property will begin eroding in year %d.\n", i,
                static_cast<int>(ceil(PI * (x * x + y * y) / 100)));
    }
    printf("END OF OUTPUT.\n");
    return 0;
}

