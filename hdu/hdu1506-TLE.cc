/**
 * HDU 1506, Largest Rectangle in a Histogram
 * DP. TLE, I suppose long long is really heavy work..
 */
#include <cstdio>
#include <cstring>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef long long LONG;
const LONG MAX_GRAM = 100001;
const LONG MAX_HEIGHT = 1000000002;

int N, height[MAX_GRAM];

int main() {
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 0; i < N; ++i) {
            scanf("%d", &height[i]);
        }
        LONG maxx = -1, temp;
        int prev, curr;
        // Raw DP equation,
        // F(i, j) is the minimum height lies in [i, j]
        // F(i, j) = min{F(i, j - 1), height(j)}, then
        // result = MAX(result, F(i, j) * (j - i + 1))
        for (int i = 0; i < N; ++i) {
            prev = MAX_HEIGHT;
            for (int j = i; j < N; ++j) {
                curr = MIN(prev, height[j]);
                temp = (LONG) curr * (j - i + 1);
                maxx = MAX(maxx, temp);
                prev = curr;
            }
        }
        printf("%lld\n", maxx);
    }
}

