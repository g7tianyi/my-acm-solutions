/**
 * POJ 1958, Strange Towers of Hanoi
 * DP
 *
 * At first k >= 1 disks on tower A are fixed and the remaining n-k disks
 * are moved from tower A to tower B using the algorithm for four towers.
 * Then the remaining k disks from tower A are moved to tower D using the
 * algorithm for three towers. At last the n - k disks from tower B are
 * moved to tower D again using the algorithm for four towers (and thereby
 * not moving any of the k disks already on tower D). Do this for all k in
 * {1, .... , n} and find the k with the minimal number of moves.
 *
 * For Hanoi3(n) problem, to move n disks from 1 to 3,
 * 1) move n-1 disks to 2                 ==> Hanoi3(n-1)
 * 2) move the biggest disk to 3          ==> 1
 * 3) move the rest n-1 disks from 2 to 3 ==> Hanoi3(n-1)
 * Hence, Hanoi3(n) = 2 * Hanoi3(n-1) + 1
 */
#include <cstdio>

int dp3[13], dp4[13];

int main() {
    int i, j;
    dp3[1] = dp4[1] = 1;
    for (i = 2; i <= 12; i++) {
        dp3[i] = 2 * dp3[i - 1] + 1;
    }
    printf("1\n");
    for (i = 2; i <= 12; i++) {
        dp4[i] = 2 + dp3[i - 1];
        for (j = 2; j < i; j++) {
            if (dp4[i] > 2 * dp4[j] + dp3[i - j]) {
                dp4[i] = 2 * dp4[j] + dp3[i - j];
            }
        }
        printf("%d\n", dp4[i]);
    }
    return 0;
}

