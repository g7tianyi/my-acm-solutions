/**
 * http://poj.org/problem?id=1674
 */

#include <iostream>

int arr[10002];

int main() {
    int T, N; // T, test cases. N, length of sequence
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        int result = 0, count, curr, next;
        for (int i = 1; i <= N; ++i) {
            if (arr[i] == i || arr[i] < 0) {
                continue;
            }

            // variable count indicates how many nodes are there in a 'cycle'
            // for the input 2 3 5 4 1, the cycle is:
            //  - index: 1 2 3 4 5
            //  - array: 2 3 5 4 1
            //    1(2) -- 2(3)
            //     |       |
            //    5(1) -- 3(5)
            // for this cycle, we need nodeCount - 1 swaps
            // another example:
            //  - index: 1 2 3 4 5
            //  - array: 2 1 5 4 3
            //    1(2)    3(5)
            //     ||      ||
            //    2(1)    5(3)
            count = 0, curr = i;
            while (arr[curr] > 0) {
                ++count;
                next = arr[curr];
                arr[curr] = -1;
                curr = next;
            }
            result += (count - 1);
        }
        printf("%d\n", result);
    }
    return 0;
}

