/**
 * POJ 1002, 487-3279
 * 1) hash => too much space, (4 * 10,000,000 / 1024) = 39062 KB...
 * 2) map  => TLE, >_<
 * 3) trie => TLE, don't DFS to check duplicates
 */
#include <cstdio>
#include <cstring>
using namespace std;

enum {
    UPPER = 100,
    LOWER = 1000
};

const int NUM_ALPHET = 26;
const int MAX_BUFFER = 256;
const int MAX_NUMBER = 10000000;
const int TABLE[NUM_ALPHET] = {
    2, 2, 2,    // A B C
    3, 3, 3,    // D E F
    4, 4, 4,    // G H I
    5, 5, 5,    // J K L
    6, 6, 6,    // M N O
    7, 7, 7, 7, // P Q R S
    8, 8, 8,    // T U V
    9, 9, 9, 9  // W X Y Z
};

int num;
int flag[MAX_NUMBER];
char buffer[MAX_BUFFER];

inline void print(int num, int boundary) {
    while (num < boundary) {
        printf("0");
        boundary /= 10;
    }
    if (num) printf("%d", num);
}

int main() {
    scanf("%d", &num);
    memset(buffer, 0, sizeof(buffer));
    int i, j, hash;
    for (i = 0; i < num; ++i) {
        scanf("%s", buffer);
        j = 0, hash = 0;
        while (buffer[j]) {
            if (buffer[j] != '-') {
                if (buffer[j] - 'A' >= 0 && buffer[j] - 'A' < 26) {
                    hash = (hash * 10 + TABLE[buffer[j] - 'A']);
                } else {
                    hash = (hash * 10 + (buffer[j] - '0'));
                }
            }
            ++j;
        }
        ++flag[hash];
        memset(buffer, 0, sizeof(buffer));
    }

    bool has_duplicates = false;
    for (i = 0; i < MAX_NUMBER; ++i) {
        if (flag[i] > 1) {
            print(i / 10000, UPPER);
            printf("-");
            print(i % 10000, LOWER);
            printf(" %d\n", flag[i]);
            has_duplicates = true;
        }
    }
    if (!has_duplicates) {
        printf("No duplicates.\n");
    }

    return 0;
}

