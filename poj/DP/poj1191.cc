/**
 * http://poj.org/problem?id=1191
 * DP
 */
#include <algorithm>
#include <cstdio>
#include <cmath>

enum {
    BOARD = 8, INF_MAX = 99999999
};

int board[BOARD][BOARD];
double ss[BOARD + 2][BOARD + 2][BOARD + 2][BOARD + 2]; // square sum
double dp[16][BOARD + 2][BOARD + 2][BOARD + 2][BOARD + 2]; // dp

/**
 * dp[k][x1][y1][x2][y2]: left-top coordinate (x1,y1) to right-bottom coordinate (x2,y2)
 * spliced k times
 *
 * ss[x1][y1][x2][y2]: square sum of left-top coordinate (x1,y1) to right-bottom coordinate (x2,y2)
 *
 * dp[k][x1][y1][x2][y2] = min {
 *     min(dp[k-1][x1][y1][f][y2]+s[f+1][y1][x2][y2], dp[k-1][f+1][y1][x2][y2]+s[x1][y1][f][y2]), // horizon
 *     min(dp[k-1][x1][y1][x2][f]+s[x1][f+1][x2][y2], dp[k-1][x1][f+1][x2][y2]+s[x1][y1][x2][f])  // vertical
 * }
 */

int main() {
    int slice;
    double sum, average;
    scanf("%d", &slice);
    sum = 0;
    for (int x1 = 0; x1 < BOARD; ++x1) {
        for (int y1 = 0; y1 < BOARD; ++y1) {
            scanf("%d", &board[x1][y1]);
            sum += board[x1][y1];
        }
    }
    average = sum / slice;

    for (int x1 = 0; x1 < BOARD; ++x1) {
        for (int y1 = 0; y1 < BOARD; ++y1) {
            for (int x2 = x1; x2 < BOARD; ++x2) {
                sum = 0;
                for (int y2 = y1; y2 < BOARD; ++y2) {
                    sum += board[x2][y2];
                    if (x1 == x2) {
                        ss[x1][y1][x2][y2] = sum;
                    } else {
                        ss[x1][y1][x2][y2] = ss[x1][y1][x2 - 1][y2] + sum;
                    }
                }
            }
        }
    }

    for (int x1 = 0; x1 < BOARD; ++x1) {
        for (int y1 = 0; y1 < BOARD; ++y1) {
            for (int x2 = x1; x2 < BOARD; ++x2) {
                for (int y2 = y1; y2 < BOARD; ++y2) {
                    ss[x1][y1][x2][y2] *= ss[x1][y1][x2][y2];
                    dp[0][x1][y1][x2][y2] = ss[x1][y1][x2][y2];
                }
            }
        }
    }

    for (int s = 1; s < slice; ++s) {
        for (int x1 = 0; x1 < BOARD; ++x1) {
            for (int y1 = 0; y1 < BOARD; ++y1) {
                for (int x2 = x1; x2 < BOARD; ++x2) {
                    for (int y2 = y1; y2 < BOARD; ++y2) {
                        dp[s][x1][y1][x2][y2] = INF_MAX;
                        for (int f = x1; f < x2; f++) { // horizontal slice
                            dp[s][x1][y1][x2][y2] = std::min(
                                    std::min(
                                            dp[s - 1][x1][y1][f][y2]
                                                    + ss[f + 1][y1][x2][y2],
                                            dp[s - 1][f + 1][y1][x2][y2]
                                                    + ss[x1][y1][f][y2]),
                                    dp[s][x1][y1][x2][y2]);
                        }
                        for (int f = y1; f < y2; f++) { // vertical slice
                            dp[s][x1][y1][x2][y2] = std::min(
                                    std::min(
                                            dp[s - 1][x1][y1][x2][f]
                                                    + ss[x1][f + 1][x2][y2],
                                            dp[s - 1][x1][f + 1][x2][y2]
                                                    + ss[x1][y1][x2][f]),
                                    dp[s][x1][y1][x2][y2]);
                        }
                    }
                }
            }
        }
    }

    double result = dp[slice - 1][0][0][BOARD - 1][BOARD - 1] / slice - average * average;
    printf("%.3f\n ", sqrt(result));

    return 0;
}

