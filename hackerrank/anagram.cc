#include <cstdio>
#include <cstring>

char buf[10001];

inline int _abs(int a) {
    return a >= 0 ? a : -a;
}

void count(char* buf, int* arr, int len) {
    for (int i = 0; i < len; ++i) {
        ++arr[buf[i]-'a'];
    }
}

int main() {
    int T;
    scanf("%d", &T);
    int left[26], right[26];
    while (T--) {
        scanf("%s", buf);
        int len = strlen(buf);
        if (len & 0x1u) {
            printf("-1\n");
            continue;
        }

        len >>= 1;
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));

        count(buf, left, len);
        count(buf + len, right, len);

        int result = 0;
        for (int i = 0; i < 26; ++i) {
            result += _abs(left[i] - right[i]);
        }
        result >>= 1;
        printf("%d\n", result);
    }
    return 0;
}

