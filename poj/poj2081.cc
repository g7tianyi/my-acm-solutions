/**
 * POJ 2081, Recaman's Sequence
 * Hash, bit operation.
 */
#include <cstdio>
#include <cstring>

const int MAX_K = 500001;

namespace hash {
    const int MAX_NUMBER = 131080;
    unsigned int flag[MAX_NUMBER];
    inline void set(int num) {
        int pos = num / 32, bit = num % 32;
        flag[pos] |= (1 << bit);
    }
    inline int get(int num) {
        int pos = num / 32, bit = num % 32;
        return flag[pos] & (1 << bit);
    }
}

int recaman[MAX_K];

int main() {
    memset(hash::flag, false, sizeof(hash::flag));
    recaman[0] = 0, hash::set(0);
    for (int i = 1; i < MAX_K; ++i) {
        if (recaman[i - 1] - i > 0 && !hash::get(recaman[i - 1] - i)) {
            recaman[i] = recaman[i - 1] - i;
        } else {
            recaman[i] = recaman[i - 1] + i;
        }
        hash::set(recaman[i]);
    }

    int K;
    while (scanf("%d", &K) != EOF && K != -1) {
        printf("%d\n", recaman[K]);
    }

    return 0;
}

