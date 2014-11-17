#include <iostream>

int main() {
    int days;
    while (scanf("%d", &days) != EOF && days) {
        // the pattern:
        //  - day : 1 2 3 4 5 6 7 8 9 10 11
        //  - coin: 1 2 2 3 3 3 4 4 4 4  5
        // day  : number of days calculated
        // value: value of coins to give
        // count: number of coins to give
        int result = 0, day = 0, value = 1, count = 1;
        while (day < days) {
            if (day + count > days) {
                count = days - day;
            }
            result += value * count;
            day += count;
            ++value;
            ++count;
        }
        printf("%d %d\n", days, result);
    }
    return 0;
}

