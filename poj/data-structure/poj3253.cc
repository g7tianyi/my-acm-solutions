/**
 * http://poj.org/problem?id=3253
 *
 * Fence Repair
 *
 * Huffman tree. priority queue.
 */

#include <cstdio>
#include <queue>

std::priority_queue<int, std::vector<int>, std::greater<int> > queue;

int main() {

    int N;
    scanf("%d", &N);

    int num;
    while (N--) {
        scanf("%d", &num);
        queue.push(num);
    }

    long long result = 0, min1, min2;
    while (!queue.empty()) {
        min1 = queue.top();
        queue.pop();
        min2 = queue.top();
        queue.pop();
        result += min1 + min2;
        if (queue.empty()) {
            break;
        }
        queue.push(min1 + min2);
    }
    printf("%lld\n", result);

    return 0;
}


