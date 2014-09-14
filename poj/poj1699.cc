/**
 * POJ 1699, Best Sequence
 *
 * DP 狀態壓縮, 旅行商問題的算法分析
 *    一個n個點的帶權有向圖，求一條路徑，使得這條路經過每個點恰好一次，
 *    並且路徑上所有邊的權值之和最小(最大)。
 *
 * 二進制表示狀態就不說了，基礎。
 * 狀態DP的經典問題中，F(i,j) 表示經過點集i中的點恰好一次，並且以j點為
 * 終點的路徑的權值和最小值。
 * F(i, j) ＝ min { F(k, s) + w(s, j) }
 * k為加入了點集j后的狀態，s則是遍歷集合k中所有的點並且F(k,s)狀態存在，
 * 點s到點j有邊存在。
 *
 */
#include <cstdio>
#include <cstring>

#define min(a, b) (a) < (b) ? (a) : (b)

enum {
    MAX_LENGTH = 24,
    MAX_WORDS  = 12,
    MAX_STATE  = (1 << 10),
    STATE_MASK = (1 << 10) - 1
};

const int MASK[12] = { 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5,
        1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11 };

char words[MAX_WORDS][MAX_LENGTH];
int commons[MAX_WORDS][MAX_WORDS];
int length[MAX_WORDS];
int dp[MAX_STATE][MAX_WORDS];

// the data volume is quite small, no need to use KMP algo
inline int interset(int former, int latter) {
    int maxlen = min(length[former], length[latter]);
    int curlen = 1, result = 0;
    while (curlen <= maxlen) {
        int i = length[former] - curlen, j = 0;
        while (i < length[former] && j < length[latter]
                 && words[former][i] == words[latter][j]) {
            ++i; ++j;
        }
        if (i == length[former]) {
            result = curlen;
        }
        ++curlen;
    }
    return result;
}

int main() {
    int test, num_words;
    scanf("%d\n", &test);
    while (test--) {
        scanf("%d\n", &num_words);
        memset(words, 0, sizeof(words));
        for (int i = 0; i < num_words; ++i) {
            scanf("%s", words[i]);
            length[i] = strlen(words[i]);
        }

        for (int i = 0; i < num_words; ++i) {
            for (int j = i + 1; j < num_words; ++j) {
                commons[i][j] = interset(i, j);
                commons[j][i] = interset(j, i);
            }
        }

        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < num_words; ++i) {
            dp[MASK[i]][i] = length[i];
        }

        int state, num_state = (1 << num_words) - 1;
        for (int i = 1; i <= num_state; ++i) {
            for (int j = 0; j < num_words; ++j) {
                if (dp[i][j] == -1 || (i & MASK[j]) == 0) {
                    continue;
                }
                for (int k = 0; k < num_words; ++k) {
                    if (j == k || (i & MASK[k])) {
                        continue;
                    }
                    state = i | MASK[k];
                    if (dp[state][k] == -1
                            || dp[state][k] > dp[i][j] + length[k] - commons[j][k]) {
                        dp[state][k] = dp[i][j] - commons[j][k] + length[k];
                        /*
                         * printf("dp[%d][%d](%d) <- dp[%d][%d](%d) - commons[%d][%d](%d) + length[%d](%d)\n",
                         *         state, k, dp[state][k],
                         *             i, j, dp[i][j],
                         *             j, k, commons[j][k],
                         *             k, length[k]);
                         */
                    }
                }
            }
        }

        int result = -1;
        for (int i = 0; i < num_words; ++i) {
            if (result == -1 || result > dp[num_state][i]) {
                result = dp[num_state][i];
            }
        }
        printf("%d\n", result);
    }
    return 0;
}

