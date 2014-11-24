/**
 * http://poj.org/problem?id=2301
 */

#include <iostream>

int score1, score2;

inline void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

inline bool solve(int sum, int diff) {
    score1 = score2 = -1;
    if (((sum + diff) & 0x1u) || ((sum - diff) & 0x1u)) {
        return false;
    }
    score1 = (sum + diff) >> 1;
    score2 = (sum - diff) >> 1;
    if (score1 >= 0 && score2 >= 0) {
        if (score1 < score2) {
            swap(score1, score2);
        }
        return true;
    }
    return false;
}

int main() {
    int T, sum, diff;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &sum, &diff);
        if(solve(sum, diff)) {
            printf("%d %d\n", score1, score2);
        } else if (solve(sum, -diff)) {
            printf("%d %d\n", score1, score2);
        } else {
            printf("impossible\n");
        }
    }
    return 0;
}

