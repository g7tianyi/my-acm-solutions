/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1227
 * DP. Very Good. Worthing Revisit.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_DEPOT = 32,
    MAX_HOTEL = 202,
    INF_MAX = 99999999
};

int pos[MAX_HOTEL];
int dp[MAX_HOTEL][MAX_DEPOT];
int cost[MAX_HOTEL][MAX_HOTEL];

inline int abs(int a) {
    return a < 0 ? -a : a;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {

    int cases = 0, num_hotel, num_depot;
    while (scanf("%d %d", &num_hotel, &num_depot) != EOF
            && (num_hotel || num_depot)) {

        for (int i = 1; i <= num_hotel; ++i) {
            scanf("%d", &pos[i]);
        }

        // cost[i][j] is the minimum cost of feeding all hotels in range [i, j]
        // it's obvious that building it in the middle of the range gives the minimum
        memset(cost, 0, sizeof(cost));
        for (int i = 1; i <= num_hotel; ++i) {
            for (int j = i; j <= num_hotel; ++j) {
                int mid = (i + j) >> 1; // the position we build the depot
                for (int k = i; k <= j; ++k) {
                    cost[i][j] += abs(pos[mid] - pos[k]);
                }
            }
        }

        memset(dp, 0, sizeof(dp));
        // dp[i][j], build j depots for the first i hotels
        // dp[i][j] = min(dp[k-1][j-1] + cost[k][i]), k in [i, j]
        // means we try to build a depot in the range [k, i]
        // so the whole cost is the minimum cost of range [0, k-1] with j-1 depots
        // plus the one covering the rang [k, i]
        for (int i = 1; i <= num_hotel; ++i) {
            dp[i][1] = cost[1][i];
        }

        int min_cost;
        for (int i = 2; i <= num_hotel; ++i) {
            for (int j = 2; j <= num_depot; ++j) {
                min_cost = INF_MAX;
                for (int k = j; k <= i; ++k) {
                    min_cost = min(min_cost, dp[k - 1][j - 1] + cost[k][i]);
                }
                dp[i][j] = min_cost;
            }
        }

        printf("Chain %d\n", ++cases);
        printf("Total distance sum = %d\n\n", dp[num_hotel][num_depot]);
    }

    return 0;
}

