/**
 * POJ 1636, Prison rearrangement
 * DFS, DP, hide very deep...
 */
#include <cstdio>
#include <cstring>

const int MAX_N = 200;

struct GROUP {
    int a, b;
};

// T, test cases. N, number of prisoners. P, danger pairs
int T, N, P;
bool danger[MAX_N][MAX_N];
GROUP group[MAX_N];

// flag => true, curr is from prison 1
// flag => false, curr is from prison 2
void DFS_GROUP(int curr, bool flag) {
    for (int i = 0; i < N; ++i) {
        if (i != curr && danger[curr][i]) {

        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        memset(danger, false, sizeof(danger));
        scanf("%d %d", &N, &P);
        int x, y;
        for (int i = 0; i < P; ++i) {
            scanf("%d %d", x, y);
            danger[x][y] = true;
        }



    }
    return 0;
}

