class Solution {
public:
    int strStr(char *haystack, char *needle) {
        if (haystack == NULL || needle == NULL) {
            return -1;
        }
        char* ps = haystack;
        char* ph = haystack;
        char* pn = needle;
        do {
            if (*pn == '\0') {
                break;
            }
            if (*pn == *ph) {
                ++ph, ++pn;
            } else {
                pn = needle;
                if (*ph == '\0') {
                    return -1;
                }
                ph = ++ps;
            }
        } while (true);
        return ps - haystack;
    }
};
