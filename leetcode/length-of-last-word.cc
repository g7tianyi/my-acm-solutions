#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

#include <cstring>
class Solution {
public:
    int lengthOfLastWord(const char* buffer) {
        if (buffer == NULL) {
            return 0;
        }
        // I'm afraid strlen is forbidden...
        int len = strlen(buffer), res = 0;
        int i = len - 1;
        while (i >= 0) {
            if (buffer[i] == ' ') {
                if (res != 0) {
                    break;
                }
            } else {
                ++res;
            }
            --i;
        }
        return res;
    }
};

static Solution solution;

char buf1[] = "Hello World";
char buf2[] = "Hello World   ";
char buf3[] = "              ";
char buf4[] = "";
char buf5[] = "HelloWorld";

int main() {
    printf("Testing %s: %d\n", buf1, solution.lengthOfLastWord(buf1));
    printf("Testing %s: %d\n", buf2, solution.lengthOfLastWord(buf2));
    printf("Testing %s: %d\n", buf3, solution.lengthOfLastWord(buf3));
    printf("Testing %s: %d\n", buf4, solution.lengthOfLastWord(buf4));
    printf("Testing %s: %d\n", buf5, solution.lengthOfLastWord(buf5));
    printf("Testing %s: %d\n", "NULL", solution.lengthOfLastWord(NULL));
    return 0;
}

