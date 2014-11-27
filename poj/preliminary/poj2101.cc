/**
 * http://poj.org/problem?id=2101
 * Honey and Milk Land
 */

#include <iostream>
#include <cmath>

int main() {
    int rc1, rc2; // river count
    scanf("%d %d", &rc1, &rc2);
    int width = 0, height = 0, len;
    for (int i = 1; i < rc1; ++i) {
        scanf("%d", &len);
        width += len;
    }
    for (int i = 1; i < rc2; ++i) {
        scanf("%d", &len);
        height += len;
    }
    if (rc1 == 1 && rc2 == 1) {
        printf("0\n");
    } else {
        printf("%d\n", (int) ceil(sqrt((double) (width * width + height * height))));
    }
    return 0;
}

