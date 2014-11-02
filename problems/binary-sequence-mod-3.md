二进制序列对3求余的问题
====
Proposed by [Hunter](https://github.com/xuhao417347761). 

給定一個二進制序列，可能很長很長，求這個序列表示的數字對3求余的結果。

> "101" -> 3 % 3 = 0

> "11001" -> 25 % 3 = 1

> "1100100011111011101100110011111001101100101011110111001110101011" -> 14482366107432743851 % 3 = 1

求解
----
## 數論結論

> (A * B) % M = [ (A % M) * (B % M) ] % M

> (A + B) % M = [ (A % M) + (B % M) ] % M

所以不僅僅對3適用吧，任意一個數字應該都可以。

###代碼
```C++
#include <cstdio>
#include <random>
#include <ctime>

const int MAX_LEN = 64;
char buf[MAX_LEN];

int mod3(int len) {
    int mod = 0;
    for (int i = len - 1; i >= 0; --i) {
        mod = ((mod << 1) + (buf[i] - '0')) % 3;
    }
    return mod;
}

// binary string to int
unsigned long btoi(int len) {
    unsigned long num = 0;
    for (int i = len - 1; i >= 0; --i) {
        num += static_cast<unsigned long>((buf[i] - '0') * pow(2.0, i));
    }
    return num;
}

void init(int len) {
    buf[--len] = '1';
    putchar(buf[len]);
    for (int i = len - 1; i >= 0; --i) {
        buf[i] = rand() & 0x1u ? '0' : '1';
        putchar(buf[i]);
    }
    putchar('\n');
}

void test(int len) {
    printf("test with length %d:\n", len);
    init(len);
    printf("%lu => %d\n\n", btoi(len), mod3(len));
}

int main() {
    srand((unsigned) time(0));
    for (int i = 1; i <= 64; ++i) {
        test(i);
    }
    return 0;
}
```

