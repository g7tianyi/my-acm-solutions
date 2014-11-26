/**
 * http://poj.org/problem?id=2388
 * Who's in the Middle
 */

#include <iostream>
#include <algorithm>

int length;
int cow[10001];

int main() {
    scanf("%d", &length);
    for (int i = 0; i < length; ++i) {
        scanf("%d", &cow[i]);
    }
    std::sort(cow, cow + length);
    printf("%d\n", cow[length >> 1]);
    return 0;
}

