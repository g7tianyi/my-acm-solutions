/**
 * HDU 1049, Climbing Worm
 */
#include<cstdio>

int main() {
    int height, upper, down;
    while (scanf("%d %d %d", &height, &upper, &down) != EOF
            && height && upper && down) {
        /**
         * the speed of the worm is (upper - down) every 2 minutes
         * when the worm reaches to a position that is no further
         * than its upper speed, it make out using just one minute
         */
        if ((height - upper) % (upper - down) == 0) {
            printf("%d\n", (((height - upper) / (upper - down)) << 1) + 1);
        } else {
            printf("%d\n", ((1 + (height - upper) / (upper - down)) << 1) + 1);
        }
    }
    return 0;
}

