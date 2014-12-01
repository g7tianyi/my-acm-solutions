/**
 * http://poj.org/problem?id=1338
 * Ugly Numbers
 * priority-queue. compare to poj2247
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>

const int factor[3] = { 2, 3, 5 };

std::priority_queue<unsigned, std::vector<unsigned>, std::greater<unsigned> > queue;
std::vector<unsigned> result;
std::set<unsigned> appeared;

int main() {
    queue.push(1), appeared.insert(1);
    unsigned size, pos;
    unsigned curr, next;
    while (scanf("%u", &pos) != EOF && pos) {
        size = result.size();
        while (size < pos) {
            curr = queue.top();
            queue.pop();
            for (int i = 0; i < 3; ++i) {
                next = curr * factor[i];
                if (appeared.find(next) == appeared.end()) {
                    queue.push(next), appeared.insert(next);
                }
            }
            result.push_back(curr);
            ++size;
        }
        printf("%d\n", result[pos - 1]);
    }
    return 0;
}

