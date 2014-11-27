/**
 * http://poj.org/problem?id=2272
 * Bullseye
 */

#include <iostream>
#include <cmath>

int main() {
    double X, Y, radius;
    int count, result[2];
    count = result[0] = result[1] = 0;
    while (scanf("%lf %lf", &X, &Y) != EOF && X != -100) {
        radius = sqrt(X * X + Y * Y);
        if (radius <= 3) {
            result[count / 3] += 100;
        } else if (radius <= 6) {
            result[count / 3] += 80;
        } else if (radius <= 9) {
            result[count / 3] += 60;
        } else if (radius <= 12) {
            result[count / 3] += 40;
        } else if (radius <= 15) {
            result[count / 3] += 20;
        }

        if (++count == 6) {
            if (result[0] == result[1]) {
                printf("SCORE: %d to %d, TIE.\n", result[0], result[1]);
            } else if (result[0] > result[1]) {
                printf("SCORE: %d to %d, PLAYER 1 WINS.\n", result[0], result[1]);
            } else {
                printf("SCORE: %d to %d, PLAYER 2 WINS.\n", result[0], result[1]);
            }
            count = result[0] = result[1] = 0;
        }
    }

    return 0;
}

