/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=1074
 *
 * DP. 状态压缩. 很好，值得重温.
 */

#include <cstdio>
#include <cstring>

const int MAX_STATE = 65536; // 1 << 16

struct COURSE {
    int cost;
    int deadline;
    char name[128];
} course[16];

struct state {
    int cost;
    int prev;
    int penalty;
};
state dp[MAX_STATE];
bool visit[MAX_STATE];

void output(int status) {
    int curr = dp[status].prev ^ status;
    int index = 0; // index of the remaining 1
    curr >>= 1;
    while (curr) {
        ++index;
        curr >>= 1;
    }
    if (dp[status].prev != 0) {
        output(dp[status].prev);
    }
    printf("%s\n", course[index].name);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int num_course;
        scanf("%d", &num_course);
        for (int i = 0; i < num_course; ++i) {
            scanf("%s %d %d", course[i].name, &course[i].deadline, &course[i].cost);
        }

        memset(visit, false, sizeof(visit));
        visit[0] = true;
        dp[0].cost = 0;
        dp[0].prev = -1;
        dp[0].penalty = 0;

        int num_state = (1 << num_course) - 1;
        for (int i = 0; i < num_state; ++i) { // try every state
            for (int j = 0; j < num_course; ++j) { // try every course
                int curr = 1 << j;
                if ((curr & i) == 0) { // not finish course j
                    int next = i | curr; // i is the prev state here
                    dp[next].cost = dp[i].cost + course[j].cost;
                    int penalty = dp[next].cost - course[j].deadline;
                    if (penalty < 0) {
                        penalty = 0;
                    }
                    penalty += dp[i].penalty;

                    if (!visit[next] || (visit[next] && penalty < dp[next].penalty)) {
                        visit[next] = true;
                        dp[next].penalty = penalty;
                        dp[next].prev = i;
                    }
                }
            }
        }

        printf("%d\n", dp[num_state].penalty);
        output(num_state);
    }
    return 0;
}

