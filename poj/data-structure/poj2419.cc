/**
 * http://poj.org/problem?id=2419
 * Forests
 */

#include <iostream>

enum {
    BYTE = sizeof(unsigned),
    OFFSET = BYTE * 8
};

unsigned hash[101][4];
bool assigned[101];

int main() {
    int P, T;
    scanf("%d %d", &P, &T);
    int person, tree;
    memset(hash, 0, sizeof(hash));
    memset(assigned, false, sizeof(assigned));
    while (scanf("%d %d", &person, &tree) != EOF && person) {
        hash[person][tree / OFFSET] |= (1 << (tree % OFFSET));
    }

    int result = P;
    T = (T + OFFSET) / OFFSET;
    for (int i = 1; i <= P; ++i) {
        if (assigned[i]) {
            continue;
        }
        for (int j = i + 1; j <= P; ++j) {
            if (!assigned[j] && memcmp(hash[i], hash[j], T * BYTE) == 0) {
                assigned[j] = true;
                --result;
            }
        }
    }
    printf("%d\n", result);

    return 0;
}

