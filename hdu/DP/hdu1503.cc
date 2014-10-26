/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1503
 *
 * DP. Advanced LCS problem.
 */

#include <cstdio>
#include <cstring>

enum CharType {
    SAME = 0, // char from string 1 and 2 are the same
    FIRST,  // char are choosen from the first string
    SECOND // char are choosen from the second string
};

const int MAX_LEN = 128;

char buf1[MAX_LEN];
char buf2[MAX_LEN];
int len1, len2;

int dp[MAX_LEN][MAX_LEN];
CharType choice[MAX_LEN][MAX_LEN];

// we can write in iteration
// but recursion here's cool
void print(int i, int j) {
    if (i == 0 && j == 0) {
        return; // end of recursion
    }

    if (i == 0 && j != 0) {
        print(i, j - 1);
        printf("%c", buf2[j - 1]);
    } else if (i != 0 && j == 0) {
        print(i - 1, j);
        printf("%c", buf1[i - 1]);
    } else if (choice[i][j] == SAME) {
        print(i - 1, j - 1);
        printf("%c", buf1[i - 1]);
    } else if (choice[i][j] == FIRST) {
        print(i - 1, j);
        printf("%c", buf1[i - 1]);
    } else {
        print(i, j - 1);
        printf("%c", buf2[j - 1]);
    }
}

int main() {
    while (scanf("%s %s", buf1, buf2) != EOF) {
        len1 = strlen(buf1), len2 = strlen(buf2);
        // Run LCS algo below
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (buf1[i - 1] == buf2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    choice[i][j] = SAME;
                } else if (dp[i][j - 1] < dp[i - 1][j]) {
                    dp[i][j] = dp[i - 1][j];
                    choice[i][j] = FIRST;
                } else {
                    dp[i][j] = dp[i][j - 1];
                    choice[i][j] = SECOND;
                }
            }
        }
        print(len1, len2);
        printf("\n");
    }
    return 0;
}

