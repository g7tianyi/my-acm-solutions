/**
 * http://poj.org/problem?id=2247
 * Humble Numbers
 * priority-queue. boring output requirement...
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>

const int factor[4] = { 2, 3, 5, 7 };

std::priority_queue<long long, std::vector<long long>, std::greater<long long> > queue;
std::vector<long long> result;
std::set<long long> appeared;

// stupid output... boring
inline void output(int pos, long long result) {
    if (pos % 10 == 1 && pos % 100 != 11) {
        printf("The %dst humble number is %lld.\n", pos, result);
    } else {
        if (pos % 10 == 2 && pos % 100 != 12) {
            printf("The %dnd humble number is %lld.\n", pos, result);
        } else {
            if (pos % 10 == 3 && pos % 100 != 13) {
                printf("The %drd humble number is %lld.\n", pos, result);
            } else {
                printf("The %dth humble number is %lld.\n", pos, result);
            }
        }
    }
}

int main() {
    queue.push(1);
    appeared.insert(1);
    unsigned size, pos;
    long long curr, next;
    while (scanf("%u", &pos) != EOF && pos) {
        size = result.size();
        while (size < pos) {
            curr = queue.top();
            queue.pop();
            for (int i = 0; i < 4; ++i) {
                next = curr * factor[i];
                if (appeared.find(next) == appeared.end()) {
                    queue.push(next);
                    appeared.insert(next);
                }
            }
            result.push_back(curr);
            ++size;
        }
        output(pos, result[pos - 1]);
    }
    return 0;
}

