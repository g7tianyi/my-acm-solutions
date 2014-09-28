/*
 ID: fairyroad1106
 LANG: C++
 TASK: frac1
 */
#include <cstdio>
#include <algorithm>

#ifdef LOCAL_MODE
#define PROGID "usaco"
#else
#define PROGID "frac1"
#endif
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

const int MAXN = 161;

struct FRACTION {
    int up, down;
    FRACTION() :
            up(0), down(0) {
    }
    FRACTION(int _up, int _down) :
            up(_up), down(_down) {
    }
};
inline bool operator<(const FRACTION& lhs, const FRACTION& rhs) {
    return lhs.up * rhs.down > lhs.down * rhs.up;
}

bool check(int a, int b) { // relatively prime or not
    int t;
    if (a < b) {
        t = a; a = b; b = t;
    }
    while ((t = a % b)) {
        a = b;
        b = t;
    }
    return b == 1;
}

inline void print(const FRACTION& f) {
    printf("%d/%d\n", f.up, f.down);
}

int N;
FRACTION fraction[MAXN];

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    scanf("%d", &N);
    print(FRACTION(0, 1));
    int i;
    for (i = 1; i < N; ++i) {
        int t = N;
        while (!check(i, t)) {
            --t;
        }
        fraction[i - 1] = FRACTION(i, t);
    }

    std::make_heap(fraction, fraction + N - 2);
    int size = N - 1, j;
    while (fraction[0].up != N - 1) {
        print (fraction[0]);
        std::pop_heap(fraction, fraction + size);
        bool flag = false;
        for (j = fraction[size - 1].down - 1; j > fraction[size - 1].up; --j) {
            if (check(fraction[size - 1].up, j)) {
                fraction[size - 1] = FRACTION(fraction[size - 1].up, j);
                flag = true;
                break;
            }
        }
        if (!flag) {
            --size;
        }
        std::push_heap(fraction, fraction + size);
    }
    if (size != 0) {
        print (fraction[0]);
    }
    print(FRACTION(1, 1));
    return 0;
}

