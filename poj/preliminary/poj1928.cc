#include <algorithm>
#include <iostream>
#include <vector>

const int picktime = 1;

struct element {
    int x, y;
    int value;
    element() : x(0), y(0), value(0) {}
    element(int x_, int y_, int v_) : x(x_), y(y_), value(v_) {}
};
std::vector<element> elems;

inline bool elem_comp(const element& elem1, const element& elem2) {
    return elem1.value > elem2.value;
}

inline int myabs(int a) {
    return a > 0 ? a : -a;
}

inline int manhattan(element& elem1, element& elem2) {
    return myabs(elem1.x - elem2.x) + myabs(elem1.y - elem2.y);
}

int main() {
    int T, M, N, K;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &M, &N, &K);
        int value;
        elems.clear();
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &value);
                if (value) {
                    element elem(i, j, value);
                    elems.push_back(elem);
                }
            }
        }

        std::sort(elems.begin(), elems.end(), elem_comp);
        std::vector<element>::iterator pos = elems.begin();
        int result = 0, distance;
        element current(0, pos->y, 0);
        for (; pos != elems.end(); ++pos) {
            // current.value => cost has already been spent
            // distance      => cost of moving to target pos
            // picktime      => cost of picking up a peanut
            // pos->y        => cost of going back to the road
            distance = manhattan(current, *pos);
            if (current.value + distance + picktime + pos->x <= K) {
                result += pos->value;
                current.value += (distance + picktime);
                current.x = pos->x, current.y = pos->y;
            } else {
                break;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

