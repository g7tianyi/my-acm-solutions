/**
 * POJ 1200, Crazy Search
 * string-hash + rabin-karp-algo
 */
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

const int MAX = 16000001;

int n, nc;

bool flag[MAX];
char buffer[MAX];
map<char, int> booker;
map<char, int>::iterator pos;

int val = 0, res = 0;

inline int get_val(char ch) {
    pos = booker.find(ch);
    if (pos == booker.end()) {
        booker[ch] = val++;
    }
    return booker[ch];
}

int main() {

    memset(flag, 0, sizeof(flag));
    memset(buffer, 0, sizeof(buffer));

    scanf("%d %d", &n, &nc);
    scanf("%s", buffer);

    int high = pow(nc, n - 1);
    int i, hash = 0, len = strlen(buffer);
    for (i = 0; i < n - 1; ++i) {
        // hash to a nc-scale number
        hash = hash * nc + get_val(buffer[i]);
    }

    for (i = n - 1; i < len; ++i) {
        hash = hash * nc + get_val(buffer[i]);
        if (!flag[hash]) {
            flag[hash] = true;
            ++res;
        }
        // shift the highest out
        hash %= high;
    }

    printf("%d\n", res);

    return 0;
}

