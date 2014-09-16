/*
 ID: fairyroad1106
 PROG: ride
 LANG: C++
 */
#include <cstdio>

#define PROGID "ride"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

char comet[8];
char group[8];

int main() {
    FILE* fin = fopen(INPUT, "r");
    FILE* fout = fopen(OUTPUT, "w");
    fscanf(fin, "%s %s", comet, group);

    long value_comet = 1;
    int i = 0;
    while (comet[i]) {
        value_comet *= (comet[i++] - 'A' + 1);
    }

    long value_group = 1;
    i = 0;
    while (group[i]) {
        value_group *= (group[i++] - 'A' + 1);
    }

    if (value_comet % 47 == value_group % 47) {
        fprintf(fout, "GO\n");
    } else {
        fprintf(fout, "STAY\n");
    }

    return 0;
}

