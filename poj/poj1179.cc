/**
 * POJ 1179 Polygon
 * dp, good dp problem
 *
 * tricky thing is,
 *  1) append a copy of the original array A in the end
 *     of A to deal with circular problem
 *  2) watch out for the array boundry, e.g., num index
 *     start with 1, sig start with 0
 *  3) be aware that the max value can be obtained from
 *     two minimum negative number
 */
#include <iostream>
#include <vector>

enum {
    MAX_EDG = 102,
    MAX_NUM = 100000000,
    MIN_NUM = -100000000
};

int N;
int num[MAX_EDG];
char sig[MAX_EDG];

int dp_max[MAX_EDG][MAX_EDG];
int dp_min[MAX_EDG][MAX_EDG];

int main() {

    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        std::cin >> sig[i] >> num[i + 1];
    }

    memcpy(num + N + 1, num + 1, N * sizeof(int));
    memcpy(sig + N, sig, N);

    for (int i = 1; i <= 2 * N; ++i) {
        for (int j = 1; j <= 2 * N; ++j) {
            if ( i == j) {
                dp_max[i][j] = num[i];
                dp_min[i][j] = num[i];
            } else {
                dp_max[i][j] = MIN_NUM;
                dp_min[i][j] = MAX_NUM;
            }
        }
    }

    for (int l = 1; l < N; ++l) { // l, length of the checking range
        for (int i = 1; i < 2 * N; ++i) { // i, start of the checking range
            // j, end of the checking range
            int j = (i + l <= 2 * N ? i + l : 2 * N), tmp;
            for (int k = i; k < j; ++k) {
                if (sig[k] == 't') {
                    tmp = dp_max[i][k] + dp_max[k + 1][j];
                    if (dp_max[i][j] < tmp) {
                        dp_max[i][j] = tmp;
                    }
                    tmp = dp_min[i][k] + dp_min[k + 1][j];
                    if (dp_min[i][j] > tmp) {
                        dp_min[i][j] = tmp;
                    }
                } else {
                    tmp = std::max(dp_max[i][k] * dp_max[k + 1][j],
                            dp_min[i][k] * dp_min[k + 1][j]);
                    if (dp_max[i][j] < tmp) {
                        dp_max[i][j] = tmp;
                    }
                    tmp = std::min(
                            std::min(
                                    std::min(dp_max[i][k] * dp_max[k + 1][j],
                                             dp_min[i][k] * dp_min[k + 1][j]),
                                    dp_min[i][k] * dp_max[k + 1][j]),
                            dp_max[i][k] * dp_min[k + 1][j]);
                    if (dp_min[i][j] > tmp) {
                        dp_min[i][j] = tmp;
                    }
                }
            }
        }
    }

    int res = MIN_NUM;
    std::vector<int> edges;
    for (int i = 1; i <= N; ++i) {
        if (res < dp_max[i][i + N - 1]) {
            res = dp_max[i][i + N - 1];
            edges.clear();
            edges.push_back(i);
        } else if (res == dp_max[i][i + N - 1]) {
            edges.push_back(i);
        }
    }

    std::cout << res << std::endl;
    for (std::vector<int>::iterator pos = edges.begin(); pos != edges.end();
            ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;

    return 0;
}

