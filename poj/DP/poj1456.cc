/**
 * POJ 1456 Supermarket
 * Greedy algo.
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_PROD = 10002;

struct PRODUCT {
    int profit, deadline;
};

bool comp(PRODUCT& p1, PRODUCT& p2) {
    return p1.profit > p2.profit;
}

PRODUCT prods[MAX_PROD];
bool sold[MAX_PROD];

int main() {

    int N;

    while (scanf("%d", &N) != EOF) {

        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &prods[i].profit, &prods[i].deadline);
        }
        std::sort(prods, prods + N, comp);

        memset(sold, false, sizeof(sold));
        int result = 0, date;
        for (int i = 0; i < N; ++i) {
            date = prods[i].deadline;
            // 1 <= di <= 10000
            // so date equals to 0 means schedule failure
            while (date && sold[date]) {
                --date;
            }
            if (date) {
                // find a date to sell product i
                sold[date] = true;
                result += prods[i].profit;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}

