Substring which occurs twice
====

Proposed by [Kevin](https://github.com/chen8913w).

> String contains only 4 char, A, T, C, G. Find the subStrings which occur twice and the length is 10. (String "AACTAAC", "AAC" occurs twice, length=3)

##解法

类似于[Robin-Karp](http://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm)，即串的Hash。

当然之类字符串匹配的算法，[KMP](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/strings/poj1226.cc)永远有发挥的空间~

```C++
#include <iostream>
#include <string>
#include <map>

typedef unsigned long ulong;

struct Entry {
    ulong start; // start pos in original text
    ulong count; // count of occurrence
    Entry() :
        start(0), count(0) {
    }
    Entry(ulong _start, ulong _count) :
        start(_start), count(_count) {
    }
};

static inline ulong hash(const char ch) {
    if (ch == 'A') {
        return 0; // 00
    }
    if (ch == 'C') {
        return 1; // 01
    }
    if (ch == 'G') {
        return 2; // 10
    }
    return 3; // 11
}

// it's assumed that
// 1) the input text contains only 4 kinds of character A C G T
// 2) the length will not exceed 32, 32 * 2 = 64, bits of a int
std::string len_k_substr(const std::string& text, unsigned len) {
    std::map<ulong, Entry> hashmap;
    /**
     * - suppose the len is 4, then the 'mask' would be 63,
     *   in binary format would be 111111
     * - further, suppose the 'value' is 72
     *   binary format is 01001000 => CAGA
     * - by applying value &= mask, we get value = 8
     *   binary format is 001000 => AGA
     *   this is how we 'pop' the front character in the hash value
     */
    ulong mask = (1 << ((len - 1) << 1)) - 1;
    ulong value = 0;
    unsigned i = 0, textlen = text.size();
    for (; i < len; ++i) {
        value = (value << 2) | hash(text[i]);
    }
    Entry entry(i - len, 1);
    hashmap.insert(std::make_pair(value, entry));

    for (; i < textlen; ++i) {
        value &= mask; // pop the front most character
        value = (value << 2) | hash(text[i]);
        if (hashmap.find(value) != hashmap.end()) {
            ++hashmap[value].count;
        } else {
            Entry entry(i - len, 1);
            hashmap.insert(std::make_pair(value, entry));
        }
    }

    std::string result;
    std::map<ulong, Entry>::const_iterator pos;
    for (pos = hashmap.begin(); pos != hashmap.end(); ++pos) {
        if (pos->second.count == 2) {
            result = text.substr(pos->second.start, len);
            break;
        }
    }

    return result;
}

// Test below...

#include <random>
#include <ctime>

enum {
    MIN_LEN = 16,
    MAX_LEN = 128
};

int main() {

    {
        std::string text("AACTAAC");
        std::cout << "original text:\n" << text << std::endl;
        std::cout << "substr of length 3 occurred twice:\n" << len_k_substr(text, 3)
                << std::endl;
    }

    srand((unsigned) time(0));

    int textlen = (rand() % (MAX_LEN >> 1)) + MIN_LEN;
    std::string text(textlen, ' ');
    for (int i = 0; i < textlen; ++i) {
        int value = rand() % 4;
        if (value == 0) {
            text[i] = 'A';
        } else if (value == 1) {
            text[i] = 'C';
        } else if (value == 2) {
            text[i] = 'G';
        } else {
            text[i] = 'T';
        }
    }
    text += text;

    std::cout << "original text:\n" << text << std::endl;

    std::cout << "substr of length 10 occurred twice:\n"
            << len_k_substr(text, 10)
            << std::endl;

    return 0;
}
```
