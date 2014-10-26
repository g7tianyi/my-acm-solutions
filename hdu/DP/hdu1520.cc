/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1520
 *
 * Tree DP.
 */
#include <vector>
#include <cstdio>
#include <cstring>

const int MAX_PEOPLE = 6002;
enum INVITATION {
    NOT_COME = 0, COME = 1
};

inline int max(int a, int b) {
    return a > b ? a : b;
}

//bool map[MAX_PEOPLE][MAX_PEOPLE]; // this will cause MLE
std::vector<int> map[MAX_PEOPLE];
bool visit[MAX_PEOPLE];

int dp[MAX_PEOPLE][2];

void DFS(int curr) {
    visit[curr] = true;
    int size = map[curr].size(), next;
    for (int j = 0; j < size; ++j) {
        next = map[curr][j];
        if (!visit[next]) {
            DFS(next);
            dp[curr][NOT_COME] += max(dp[next][COME], dp[next][NOT_COME]);
            dp[curr][COME] += dp[next][NOT_COME];
        }
    }
    // printf("dp[%d][come]=%d, dp[%d][not_come]=%d\n", curr, dp[curr][COME], curr,
    //            dp[curr][NOT_COME]);
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        int val;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &val);
            dp[i][NOT_COME] = 0, dp[i][COME] = val;
        }
        memset(map, false, sizeof(map));
        int employee, employer;
        while (scanf("%d %d", &employee, &employer) != EOF
                && (employee || employer)) {
            map[employee].push_back(employer);
            map[employer].push_back(employee);
        }

        memset(visit, false, sizeof(visit));
        DFS(1);
        printf("%d\n", max(dp[1][0], dp[1][1]));
    }
    return 0;
}

