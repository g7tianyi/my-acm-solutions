/**
 * POJ 1989, The Cow Lineup
 */
#include <cstdio>
#include <cstring>

const int MAX_K = 10001;
bool flag[MAX_K];

int main() {
    int N, K, breed, num = 0, result = 0;
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &breed);
        if (!flag[breed]) {
            flag[breed] = true;
            ++num;
            if (num == K) {
                ++result, num = 0;
                memset(flag, 0, sizeof(flag));
            }
        }
    }
    printf("%d\n", result + 1);
    return 0;
}

