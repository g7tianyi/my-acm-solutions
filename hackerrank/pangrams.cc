#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char buf[1002];

int main() {
    fgets(buf, sizeof(buf), stdin);

    int count[26];
    memset(count, 0, sizeof(count));

    int len = strlen(buf);
    for (int i = 0; i < len; ++i) {
        if (buf[i] - 'a' >= 0 && buf[i] - 'a' < 26) {
            ++count[buf[i] - 'a'];
        } else if (buf[i] - 'A' >= 0 && buf[i] - 'A' < 26) {
            ++count[buf[i] - 'A'];
        }
    }

    bool pangram = true;
    for (int i = 0; i < 26; ++i) {
        if (count[i] == 0) {
            pangram = false;
            break;
        }
    }

    if (pangram) {
        printf("pangram\n");
    } else {
        printf("not pangram\n");
    }

    return 0;
}

