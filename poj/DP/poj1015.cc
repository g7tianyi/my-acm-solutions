/**
 * http://poj.org/problem?id=1015
 * DP. packing problem
 */

#include <algorithm>
#include <cstring>
#include <cstdio>

enum {
    MAX_VAL = 20,
    MAX_MAN = 202,
    MAX_SUM = ((MAX_VAL * MAX_VAL) << 1) + MAX_VAL + 1
};

int N, M;
int diff[MAX_MAN];
int summ[MAX_MAN];
int people[MAX_MAN];
int dp[MAX_VAL + 1][MAX_SUM];
int path[MAX_VAL + 1][MAX_SUM];

// check if k not in the prev-path
bool exists(int i, int j, int k) {
    while (i > 0 && path[i][j] != k) {
        j -= diff[path[i][j]];
        --i;
    }
    return i > 0;
}

void print_path(int sum) {
    for (int i = 0, j = M, k = sum; i < M; ++i) {
        people[i] = path[j][k];
        k -= diff[path[j][k]];
        --j;
    }
    std::sort(people, people + M);
    for (int i = 0; i < M; ++i) {
        printf(" %d", people[i]);
    }
    printf("\n\n");
}

int main() {
    int cases = 0;
    while (scanf("%d %d", &N, &M) != EOF && (N || M)) {
        int prosecution, defence;
        for (int i = 1; i <= N; ++i) {
            scanf("%d %d", &prosecution, &defence);
            diff[i] = prosecution - defence;
            summ[i] = prosecution + defence;
        }

        memset(dp, -1, sizeof(dp));
        memset(path, 0, sizeof(path));

        int shift = M * MAX_VAL;
        dp[0][shift] = 0;

        // dp[i][j], max (prosecution + defence) when we get j = prosecution - defence
        // from the former i people
        // so, this is just a packing problem
        // we can view (prosecution - defence) as the "capacity"
        // and "prosecution + defence" as the "value"
        // intuitive 0-1 problem
        for (int i = 1; i <= M; ++i) { // loop M selected people
            for (int j = 0; j <= (shift << 1); ++j) { // try all possible diff value
                if (dp[i - 1][j] >= 0) {
                    for (int k = 1; k <= N; ++k) { // try all possible people
                        if (dp[i][j + diff[k]] < dp[i - 1][j] + summ[k]
                                && !exists(i - 1, j, k)) { // ensure k has not been selected before
                            dp[i][j + diff[k]] = dp[i - 1][j] + summ[k];
                            path[i][j + diff[k]] = k;
                        }
                    }
                }
            }
        }

        int k = 0;
        for (k = 0; k <= 2 * shift; ++k) {
            if (dp[M][shift + k] >= 0 || dp[M][shift - k] >= 0) {
                break;
            }
        }
        int result = dp[M][shift + k] > dp[M][shift - k] ? shift + k : shift - k;

        printf("Jury #%d\n", ++cases);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",
                (dp[M][result] + result - shift) >> 1,
                (dp[M][result] - result + shift) >> 1);
        print_path(result);
    }

    return 0;
}

