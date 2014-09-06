/**
 * POJ 1157, LITTLE SHOP OF FLOWERS
 * dp
 */
#include <cstdio>
#include <cstring>

#define max(a, b) (a) > (b) ? (a) : (b)

const int MAX = 101;
const int MIN = -51 * MAX;

int F, V;
int values[MAX][MAX];

int main() {

    scanf("%d %d", &F, &V);

    int i, j;
    for (i = 0; i < F; ++i) {
        for (j = 0; j < V; ++j) {
            scanf("%d", &values[i][j]);
        }
    }

    //
    // F(i, j) represents the max aesthetic value of arranging the
    // first i flowers in the first j vases
    //   * F(i, j) = max { F(i-1, j-1) + values(i, j), F(i, j-1) }
    // this equation means whether we arrange the i-th flower into
    // vase j, or, into any one of the first j - 1 vases.
    //
    for (j = 1; j < V; ++j) {
        if (values[0][j] < values[0][j - 1]) {
            values[0][j] = values[0][j - 1];
        }
    }

    for (i = 1; i < F; ++i) {
        for (j = 0; j < i; ++j) {
            values[i][j] = MIN;
        }
        values[i][j] += values[i - 1][j - 1];
    }

    for (i = 1; i < F; ++i) {
        for (j = i + 1; j < V; ++j) {
            values[i][j] = max(values[i - 1][j - 1] + values[i][j],
                    values[i][j - 1]);
        }
    }

    printf("%d\n", values[F - 1][V - 1]);

    return 0;
}

