/**
 * http://poj.org/problem?id=2051
 * Argus
 *
 * priority_queue
 */

#include <iostream>
#include <queue>

struct Query {
    int runtime;
    int queryId;
    int period;
};

inline bool operator<(const Query& lhs, const Query& rhs) {
    if (lhs.runtime != rhs.runtime) {
        return lhs.runtime > rhs.runtime;
    }
    return lhs.queryId > rhs.queryId;
}

// try to implement priority_queue in raw C++ ~
std::priority_queue<Query> queue;

int main() {
    char buf[16];
    int queryId, period;
    while (scanf("%s", buf) != EOF && buf[0] != '#') {
        scanf("%d %d", &queryId, &period);
        Query query;
        query.queryId = queryId;
        query.period  = period;
        query.runtime = period;
        queue.push(query);
    }

    int queryCount;
    scanf("%d", &queryCount);
    while (queryCount--) {
        Query query = queue.top();
        queue.pop();
        printf("%d\n", query.queryId);
        query.runtime += query.period;
        queue.push(query);
    }

    return 0;
}

