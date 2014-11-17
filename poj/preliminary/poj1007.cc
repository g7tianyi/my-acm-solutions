/**
 * http://poj.org/problem?id=1007
 */

#include <algorithm>
#include <iostream>

struct DNA {
    int  inv; // count of the inversions
    char seq[51];
};

inline bool info_comp(const DNA& lhs, const DNA& rhs) {
    return lhs.inv < rhs.inv;
}

DNA dna[101];
int dp[4];

int main() {
    int len, num;
    scanf("%d %d", &len, &num);
    for (int i = 0; i < num; ++i) {
        scanf("%s", dna[i].seq);
        memset(dp, 0, sizeof(dp));
        for (int j = 0, k; j < len; ++j) {
            if (dna[i].seq[j] == 'A') {
                k = 0;
                dna[i].inv += (dp[1] + dp[2] + dp[3]);
            } else if (dna[i].seq[j] == 'C') {
                k = 1;
                dna[i].inv += (dp[2] + dp[3]);
            } else if (dna[i].seq[j] == 'G') {
                k = 2;
                dna[i].inv += dp[3];
            } else { // 'T'
                k = 3;
            }
            ++dp[k];
        }
    }

    std::sort(dna, dna + num, info_comp);
    for (int i = 0; i < num; ++i) {
        printf("%s\n", dna[i].seq);
    }
    return 0;
}

