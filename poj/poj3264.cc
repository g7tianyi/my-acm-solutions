/**
 * http://poj.org/problem?id=3264
 *
 * RMQ.
 */
#include<cstring>
#include<cstdio>

enum QueryType {
    QUERT_MAX, QUERY_MIN
};

static const int MAX_COW = 50005;

int height[MAX_COW];

struct RMQ {
public:
    void init(int size) {
        this->size = size;
        for (int i = 1; i <= size; ++i) {
            maxValue[i][0] = height[i];
            minValue[i][0] = height[i];
        }
        for (int j = 1; (1 << j) <= size; ++j) {
            for (int i = 1; i + ((1 << j) - 1) <= size; ++i) {
                maxValue[i][j] = max(maxValue[i][j - 1],
                        maxValue[i + (1 << (j - 1))][j - 1]);
                minValue[i][j] = min(minValue[i][j - 1],
                        minValue[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    inline int query(int first, int last, QueryType queryType) {
        int k = log(last - first + 1);
        if (queryType == QUERT_MAX) {
            return max(maxValue[first][k], maxValue[last - (1 << k) + 1][k]);
        } else {
            return min(minValue[first][k], minValue[last - (1 << k) + 1][k]);
        }
    }

private:
    inline int max(int a, int b) {
        return a > b ? a : b;
    }
    inline int min(int a, int b) {
        return a < b ? a : b;
    }
    inline int log(int n) {
        int k = 0;
        while (n) {
            ++k;
            n >>= 1;
        }
        return k - 1;
    }

private:
    int size;
    int maxValue[MAX_COW][20];
    int minValue[MAX_COW][20];
};

static RMQ rmq;

int main() {

    int num_cow, num_query;
    scanf("%d %d", &num_cow, &num_query);
    for (int i = 1; i <= num_cow; ++i) {
        scanf("%d", &height[i]);
    }

    rmq.init(num_cow);
    int first, last;
    for (int i = 1; i <= num_query; ++i) {
        scanf("%d %d", &first, &last);
        printf("%d\n",
                rmq.query(first, last, QUERT_MAX) - rmq.query(first, last, QUERY_MIN));
    }

    return 0;
}

