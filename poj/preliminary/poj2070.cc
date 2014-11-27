/**
 * http://poj.org/problem?id=2070
 * Filling Out the Team
 */

#include <iostream>

enum PlayerType {
    WideReceiver,
    Lineman,
    Quarterback,
    PlayerTypeCount
};

enum PropertyType {
    Speed,
    Weight,
    Strength,
    PropertyTypeCount
};

double criterion[PlayerTypeCount][PropertyTypeCount] = {
    { 4.5, 150.0, 200.0 },
    { 6.0, 300.0, 500.0 },
    { 5.0, 200.0, 300.0 }
};

char player_name[PlayerTypeCount][16] = {
    "Wide Receiver",
    "Lineman",
    "Quarterback"
};

int main() {
    double speed, weight, strength;
    while (scanf("%lf %lf %lf", &speed, &weight, &strength)) {
        if (!(speed || weight || strength)) {
            break;
        }

        bool proper = false;
        for (int i = 0; i < PlayerTypeCount; ++i) {
            if (speed <= criterion[i][Speed]
                  && weight >= criterion[i][Weight]
                  && strength >= criterion[i][Strength]) {
                proper = true;
                printf("%s ", player_name[i]);
            }
        }
        if (!proper) {
            printf("No positions");
        }
        printf("\n");
    }
    return 0;
}

