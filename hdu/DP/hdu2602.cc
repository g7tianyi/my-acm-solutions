/**
 * HDU 2602, Bone Collector
 * dp. classical 0-1 packing problem
 */
#include <cstdio>
#include <cstring>

inline int max(int a, int b) {
    return a > b ? a : b;
}
enum {
    MAX_BONE = 1002, MAX_VOLUME = 1002
};
int value[MAX_BONE], volume[MAX_BONE], dp[MAX_VOLUME];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, V;
        scanf("%d %d", &N, &V);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &value[i]);
        }
        for (int i = 0; i < N; ++i) {
            scanf("%d", &volume[i]);
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < N; ++i) {
            for (int j = V; j >= volume[i]; --j) {
                dp[j] = max(dp[j], dp[j - volume[i]] + value[i]);
            }
        }
        printf("%d\n", dp[V]);
    }

    return 0;
}

