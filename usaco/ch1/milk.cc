/*
 ID: fairyroad1106
 PROG: milk
 LANG: C++
 */
#include <cstdio>
#include <algorithm>

#define PROGID "milk"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

const int MAX_FARMER = 5005;

struct FARMER {
    int price, count;
    FARMER() : price(0), count(0) {}
};
FARMER farmer[MAX_FARMER];

inline bool operator<(const FARMER& lhs, const FARMER& rhs) {
    if (lhs.price != rhs.price) {
        return lhs.price < rhs.price;
    }
    return lhs.count < rhs.count;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int total, num;
    scanf("%d %d", &total, &num);
    for (int i = 0; i < num; ++i) {
        scanf("%d %d", &farmer[i].price, &farmer[i].count);
    }

    std::sort(farmer, farmer + num);
    int i = 0, cost = 0;
    while (total) {
        if (total < farmer[i].count) {
            cost += total * farmer[i].price;
            total = 0;
        } else {
            cost += farmer[i].count * farmer[i].price;
            total -= farmer[i].count;
        }
        ++i;
    }
    printf("%d\n", cost);

    return 0;
}

