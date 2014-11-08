#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int stick[1001];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &stick[i]);
    }
    
    // 1. one solution is to create a min-heap
    //    each time we element in the top of the heap
    //    is the length we cut from all left stick
    // 2. another idea is to sort the sticks
    std::sort(stick, stick + N);
    int curr = 0, left = N;
    int cut = stick[curr];
    printf("%d\n", left);
    while (true) {
        int count = 1;
        while (curr + count < N 
               && stick[curr + count] == stick[curr]) {
            ++count;
        }
        left -= count;
        if (left) {
            printf("%d\n", left);
            curr += count;
        } else {
            break;
        }
    }
    
    return 0;
}

