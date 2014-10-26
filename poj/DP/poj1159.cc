/**
 * POJ 1159, Palindrome
 *
 * F(i,j), number of letters need to be inserted
 * F(i, j) = {
 *   str(i) == str(j), F(i + 1, j - 1),
 *   str(i) != str(j), MIN { F(i + 1, j), F(i, j - 1) } + 1
 * }
 *
 * Another choice is using the LCS idea.
 * Let s' be the reversed copy of s,
 * the number of letters need to be inserted is
 *   len(s)-LCS(s, s')
 * By the trick of sliding array, we can optimize the space cost to O(N)
 */
#include <cstdio>
#include <cstring>

const int MAX_LEN = 5001;
int N;
char buf[MAX_LEN];
short int pal[MAX_LEN][MAX_LEN];

inline int min(int a, int b) {
    return a < b ? a : b;
}

short int dfs(int start, int end) { // both start and end are inclusive
    if (start >= end) {
        pal[start][end] = 0;
        return 0;
    }
    if (pal[start][end] != -1) {
        return pal[start][end];
    }

    if (buf[start] == buf[end]) {
        pal[start][end] = dfs(start + 1, end - 1);
    } else {
        pal[start][end] = min(dfs(start, end - 1), dfs(start + 1, end)) + 1;
    }

    return pal[start][end];
}

int main() {
    while (scanf("%d\n", &N) != EOF) {
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        memset(pal, -1, sizeof(pal));
        printf("%d\n", dfs(0, N - 1));
    }
    return 0;
}

