/**
 * http://poj.org/problem?id=1789
 * MST, standard prime algo.
 * the fancy thing is, modeling the problem into a MST problem
 */

#include <cstdio>

enum {
    MAX_TYPE = 2001, TYPE_LEN = 8, INF_MAX = 99999999
};

char type[MAX_TYPE][TYPE_LEN];
int graph[MAX_TYPE][MAX_TYPE];
int queue[MAX_TYPE];

int main() {
    int size, diff;
    while (scanf("%d", &size) != EOF && size) {
        for (int i = 1; i <= size; ++i) {
            scanf("%s", &type[i]);
            for (int j = 1; j <= i; ++j) {
                diff = 0;
                // calculate the difference, i.e., cost, to each type before
                for (int k = 0; k < TYPE_LEN - 1; ++k) {
                    if (type[i][k] != type[j][k]) {
                        ++diff;
                    }
                    graph[i][j] = graph[j][i] = diff;
                }
            }
        }

        int result = 0;
        for (int i = 1; i <= size; ++i) {
            queue[i] = graph[1][i];
        }
        queue[1] = 0;

        for (int i = 1; i <= size - 1; ++i) {
            int min_cost = INF_MAX, next;
            // choose an edge with minimum cost
            for (int j = 1; j <= size; ++j) {
                if (queue[j] != 0 && min_cost > queue[j]) {
                    min_cost = queue[j];
                    next = j;
                }
            }

            result += queue[next];
            queue[next] = 0;

            // update the queue
            for (int j = 1; j <= size; ++j) {
                if (queue[j] != 0 && queue[j] > graph[next][j]) {
                    queue[j] = graph[next][j];
                }
            }
        }

        printf("The highest possible quality is 1/%d.\n", result);
    }
    return 0;
}

