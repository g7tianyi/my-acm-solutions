/*
 ID: fairyroad1106
 PROG: barn1
 LANG: C++
 */
#include <cstdio>
#include <algorithm>
#include <functional>

#define PROGID "barn1"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

const int MAX_STALL = 202;
int pos[MAX_STALL];

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int nBoard, nBarn, nCow, start = MAX_STALL, end = -1;
    scanf("%d %d %d", &nBoard, &nBarn, &nCow);
    for (int i = 0; i < nCow; ++i) {
        scanf("%d", &pos[i]);
        start = std::min(start, pos[i]);
        end = std::max(end, pos[i]);
    }
    int sum = end - start + 1;

    std::sort(pos, pos + nCow);
    int prev = pos[0];
    for (int i = 1; i < nCow; ++i) {
        pos[i - 1] = pos[i] - prev - 1;
        prev = pos[i];
    }

    std::sort(pos, pos + nCow - 1, std::greater<int>());
    for (int i = 0; i < std::min(nBoard, nCow) - 1; ++i) {
        sum -= pos[i];
    }
    printf("%d\n", sum);

    return 0;
}

