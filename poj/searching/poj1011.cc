/**
 * http://poj.org/problem?id=1011
 *
 * DFS.
 */

#include <iostream>

int total, maxlen;
int stick[64];

// currlen: length of current stick, we're trying to round it to unitlen
// unitlen: length of each original stick we're "assuming"
// maxlen : max length of the cut stick
// count  : count of sticks we should collect
bool dfs(int currlen, int count, const int unitlen) {
    if (count <= 0) {
        return true;
    }
    for (int len = maxlen, nextlen; len > 0; --len) {
        if (stick[len] == 0) {
            continue;
        }
        nextlen = currlen + len;
        if (nextlen == unitlen) {
            --stick[len];
            if (dfs(0, count - 1, unitlen)) {
                return true;
            }
            ++stick[len];
        } else if (nextlen < unitlen) {
            --stick[len];
            if (dfs(nextlen, count, unitlen)) {
                return true;
            }
            ++stick[len];
        }
        if (currlen == 0) {
            // no matter what sticks are left, it must be OK to
            // composite the "new"(currlen == 0) stick
            break;
        }
    }
    return false;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF && N) {
        total = 0, maxlen = -1;
        memset(stick, 0, sizeof(stick));
        for (int i = 0, len; i < N; ++i) {
            scanf("%d", &len);
            ++stick[len];
            total += len;
            maxlen = len > maxlen ? len : maxlen;
        }

        int result = total;
        for (int j = maxlen, i; j < total; ++j) { // j is unitlen
            if (total % j) {
                continue;
            }
            i = total / j; // i is stick count
            if (dfs(0, i, j)) {
                result = j;
                break;
            }
        }

        printf("%d\n", result);
    }
    return 0;
}

