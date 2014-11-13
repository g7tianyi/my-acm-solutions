/**
 * POJ 2411, Mondriaan's Dream
 * DP. State Compression. Very good DP state compression problem.
 * Receive a WA for long long >_< ~~~  
 *
 * State:
 * 1 for vertical placement, 0 for horizontal or doesn't palce anything
 * e.g., 100111 means
 *  | - - | | |
 *  |     | | |
 * the next row can only be,
 *  000000
 *  011000
 */
#include <cstdio>
#include <cstring>

typedef long long MYLONG;
enum {
    MAX_WIDTH = 12, MAX_HEIGHT = 12
};
const int STATE[MAX_WIDTH] = {
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5,
    1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11
};

int height, width;
MYLONG dp[2][1 << MAX_WIDTH];

void get_legal_states(int pos, int cur) {
    if (pos >= width) {
        return;
    }
    if (pos == width - 2) {
        dp[0][cur] = 1;
    }
    if (pos == width - 1) {
        dp[0][cur | STATE[pos]] = 1;
    }
    get_legal_states(pos + 1, cur | STATE[pos]); // try vertical placement
    get_legal_states(pos + 2, cur); // try horizontal placement
}

bool match(int curr, int prev) {
    if (curr & prev) {
        return false;
    }
    int comb = curr | prev, count = 0; // count of zeros
    for (int i = 0; i < width; ++i) {
        if (!(comb & STATE[i])) {
            ++count;
        } else {
            if (count & 0x1u) {
                return false;
            }
            count = 0;
        }
    }
    return !(count & 0x1u);
}

int main() {
    while (scanf("%d %d", &height, &width) != EOF && height && width) {
        memset(dp, 0, sizeof(dp));
        get_legal_states(0, 0);

        int curr = 0, prev = 1;
        int num_state = (1 << width);
        MYLONG result = 0;
        if (height > 1) {
            for (int i = 1; i < height - 1; ++i) { // try each row
                curr ^= 1, prev ^= 1; // sliding array
                memset(dp[curr], 0, sizeof(dp[0]));
                for (int j = 0; j < num_state; ++j) { // try each state in current row
                    for (int k = 0; k < num_state; ++k) { // try each state in previous row
                        if (match(j, k)) {
                            dp[curr][j] += dp[prev][k];
                        }
                    }
                }
            }
            for (int k = 0; k < num_state; ++k) {
                if (match(0, k)) { // the last row can only place all zeros
                    result += dp[curr][k];
                }
            }
        } else {
            result += dp[curr][0];
        }
        printf("%lld\n", result);
    }

    return 0;
}

