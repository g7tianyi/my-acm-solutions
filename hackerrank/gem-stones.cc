#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char buf[101];
int count_map[27][101];

int main() {
    int N;
    scanf("%d", &N);
    
    memset(count_map, 0, sizeof(count_map));
    for (int i = 1; i <= N; ++i) {
        scanf("%s", buf);
        int len = strlen(buf), char_idx;
        for (int j = 0; j < len; ++j) {
            char_idx = buf[j] - 'a';
            if (count_map[char_idx][i] == 0) {
                ++count_map[char_idx][0];
                ++count_map[char_idx][i];
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < 26; ++i) {
        if(count_map[i][0] == N) {
            ++result;
        }
    }
    printf("%d\n", result);
    
    return 0;
}

