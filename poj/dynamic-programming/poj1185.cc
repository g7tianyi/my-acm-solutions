/**
 * POJ 1185
 * DP
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_STATE = 64, MAX_ROWS = 101, MAX_COLUMNS = 12
};

int num_row, num_column, state_count;
int legal_states[MAX_STATE], row_states[MAX_ROWS], num_people[MAX_STATE];
int DP[2][MAX_STATE][MAX_STATE];
bool grid[MAX_ROWS][MAX_COLUMNS];
char buffer[MAX_COLUMNS];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int count_people(int state) {
    // count how many '1' in the binary format of state
    int num = 0;
    while (state) {
        ++num;
        state &= (state - 1);
    }
    return num;
}

inline bool is_legal(int state) {
    return !((state & (state << 1)) || (state & (state << 2)));
}

void init_state(int end_state) {
    state_count = 0;
    for (int curr_state = 0; curr_state < end_state; ++curr_state) {
        if (is_legal(curr_state)) {
            legal_states[state_count] = curr_state;
            num_people[state_count] = count_people(curr_state);
            ++state_count;
        }
    }
}

int main() {

    scanf("%d%d", &num_row, &num_column);
    for (int i = 0; i < num_row; i++) {
        scanf("%s", buffer);
        row_states[i] = 0;
        for (int j = 0; j < num_column; j++) {
            row_states[i] <<= 1;
            row_states[i] |= buffer[j] == 'H' ? 1 : 0;
        }
    }

    init_state(1 << num_column);

    // dp[r][i][j], max when row r is in state i and row r-1 is in state j
    // dp[r][i][j] = max(dp[r][i][j], dp[r-1][j][k] + num_people[i]);
    memset(DP[0], -1, sizeof(DP[0]));
    for (int i = 0; i < state_count; i++) {
        if (row_states[0] & legal_states[i]) {
            // since grid with hill flagged with 1
            // entering here means legal state conflict with battle row
            continue;
        }
        DP[0][i][0] = num_people[i];
    }

    int T1 = 1, T2 = 0;
    for (int r = 1; r < num_row; ++r) {
        T1 ^= 1, T2 ^= 1; // sliding window, save memories
        memset(DP[T2], -1, sizeof(DP[0]));

        for (int i = 0; i < state_count; ++i) { // try all states in row i
            if (legal_states[i] & row_states[r]) {
                // state conflicts with row state (with hills)
                continue;
            }

            for (int j = 0; j < state_count; ++j) { // try all states in row j
                if ((legal_states[i] & legal_states[j]) // state i and j conflict, share one/some column(s)
                        || (legal_states[j] & row_states[r - 1])) { // state conflicts with row state (with hills)
                    continue;
                }

                for (int k = 0; k < state_count; ++k) { // try all states in row k
                    if ((legal_states[i] & legal_states[k])
                            || (legal_states[k] & legal_states[j])
                            || DP[T1][j][k] == -1) {
                        continue;
                    }
                    DP[T2][i][j] = max(DP[T2][i][j],
                            DP[T1][j][k] + num_people[i]);
                }
            }
        }
    }

    int result = -1;
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < state_count; j++) {
            result = max(result, DP[T2][i][j]);
        }
    }
    printf("%d\n", result);

    return 0;
}

