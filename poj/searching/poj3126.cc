/**
 * http://poj.org/problem?id=3126
 * prime number. bfs
 */

#include <iostream>
#include <deque>

enum {
    UPPER = 10000,
    COUNT = 1200
};
bool flag[UPPER];
int  hash[UPPER];
int  graph[COUNT][COUNT];
std::deque<int> queue;

void prepare() {
    // construct the prime number table
    memset(flag, true, sizeof(flag));
    flag[0] = false, flag[1] = false;
    for (int i = 2; i < UPPER; ++i) {
        if (flag[i]) {
            // 欲刪掉質數 i 的倍數之時，早已刪掉 1 倍到 i-1 倍了，直接從 i 倍開始。
            for (int j = i * i; j < UPPER; j += i) {
                flag[j] = false;
            }
        }
    }

    // construct the graph
    memset(graph, 0, sizeof(graph));
    memset(hash, 0, sizeof(hash));
    int nums[4];
    for (int num = 1000, idx = 0; num < UPPER; ++num) {
        if (!flag[num]) {
            continue;
        }

        hash[num] = idx++;

        int curr = num;
        int pow = 1000;
        for (int i = 0, j = curr; i < 4; ++i) {
            nums[i] = j / pow;
            j %= pow;
            pow /= 10;
        }

        int base, next, shift, count;
        for (int i = 0; i < 4; ++i) {
            base = 0, pow = 1000;
            for (int j = 0; j < 4; ++j) {
                if (j != i) {
                    base += nums[j] * pow;
                } else {
                    shift = pow;
                }
                pow /= 10;
            }

            for (int j = (i ? 0 : 1); j < 10; ++j) {
                next = base + j * shift;
                if (next != curr && flag[next]) {
                    count = ++graph[hash[curr]][0];
                    graph[hash[curr]][count] = next;
                }
            }
        }
    }
#if 0
    for (int i = 0; i < COUNT; ++i) {
        if (graph[i][0]) {
            for (int j = 1; j <= graph[i][0]; ++j) {
                printf("%d ", graph[i][j]);
            }
            printf("\n");
        }
    }
#endif
}

int main() {
    prepare();

    int N, source, target;
    scanf("%d", &N);
    while (N--) {
        scanf("%d %d", &source, &target);

        memset(flag, false, sizeof(flag));
        flag[source] = true;

        queue.clear();
        queue.push_back(source);
        queue.push_back(0);

        int result = 0;
        while (!queue.empty()) {
            int curr = queue.front();
            queue.pop_front();
            if (curr == 0) {
                if (!queue.empty()) {
                    queue.push_back(0);
                }
                ++result;
                continue;
            }
            if (curr == target) {
                break;
            }
            int idx = hash[curr];
            for (int i = 1; i <= graph[idx][0]; ++i) {
                if (!flag[graph[idx][i]]) { // not visited
                    flag[graph[idx][i]] = true;
                    queue.push_back(graph[idx][i]);
                }
            }
        }
        printf("%d\n", result);
    }

    return 0;
}

