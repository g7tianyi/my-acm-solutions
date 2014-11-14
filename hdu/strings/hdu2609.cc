/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=2609
 *
 * string. minimal string rotation.
 */

#include <iostream>
#include <cstring>
#include <string>
#include <set>

char word[128];
char buff[128];
std::set<std::string> hasher;

// I learned this algorithm from here, thanks~
// http://blog.csdn.net/runninghui/article/details/11694089
//
// i is the start pos of the "former" string
// j is the start pos of the "latter" string
// k is the length of the substring under checking right now
//
// suppose str is EFAASDFBC
// "former" string here is: EFAASDFBC
// "latter" string here is: FAASDFBCE
int minimal_string_rotation(char* str, int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        if (k == len) {
            break;
        }
        if (i == j) {
            ++j;
        }
        int endi = (i + k) % len, endj = (j + k) % len;
        if (str[endi] > str[endj]) {
            i += (k + 1);
            k = 0;
        } else if (str[endi] < str[endj]) {
            j += (k + 1);
            k = 0;
        } else {
            ++k;
        }
    }
    return i;
}

int main() {
    int count;
    while (scanf("%d", &count) != EOF) {
        int pos, len;
        hasher.clear();
        for (int i = 0; i < count; ++i) {
            scanf("%s", word);
            len = strlen(word);
            pos = minimal_string_rotation(word, len);
            memcpy(buff, word + pos, len - pos);
            memcpy(buff + len - pos, word, pos);
            std::string str(buff);
            if (hasher.find(str) == hasher.end()) {
                hasher.insert(str);
            }
        }
        printf("%lu\n", hasher.size());
    }
    return 0;
}

