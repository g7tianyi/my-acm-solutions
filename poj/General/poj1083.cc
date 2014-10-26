/**
 * POJ 1083 Moving Tables
 * "bitmap" algorithm, all corridor with the bigest occupying count is the result
 */
#include <cstdio>
#include <cstring>

static const int MAX_ROOM = 201;

int corridor[MAX_ROOM];

template<typename T>
inline void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

int main() {
    int cases;
    scanf("%d", &cases);

    int tables, from, to, result;
    while (cases--) {
        memset(corridor, 0, sizeof(corridor));

        scanf("%d", &tables);
        for (int i = 0; i < tables; ++i) {
            scanf("%d %d", &from, &to);
            if (from > to) {
                swap(from, to);
            }
            from = (from - 1) >> 1;
            to = (to - 1) >> 1;
            for (int k = from; k <= to; ++k) {
                ++corridor[k];
            }
        }

        result = -1;
        for (int i = 0; i < MAX_ROOM; ++i) {
            if (result < corridor[i]) {
                result = corridor[i];
            }
        }

        printf("%d\n", result * 10);
    }

    return 0;
}

