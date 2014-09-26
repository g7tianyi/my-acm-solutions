/**
 * HDU 1002, A + B Problem II.
 * big number addition
 * Give a try to C++ operator overloading
 */
#include <iostream>
#include <cstring>

const int MAX_DIGIT = 1024;

struct BIGINT {
    int arr[MAX_DIGIT], len;
    BIGINT() {
        clear();
    }
    inline void clear() {
        memset(arr, 0, sizeof(arr));
        len = 0;
    }
    inline void set(char* buffer) {
        len = strlen(buffer);
        for (int i = 0; i < len; ++i) {
            arr[len - 1 - i] = buffer[i] - '0';
        }
    }
};
BIGINT lhs, rhs;

inline BIGINT operator+(const BIGINT& left, const BIGINT& right) {
    BIGINT res;
    int i = 0, j = 0, k = 0;
    for (; i < left.len && j < right.len; ++i, ++j) {
        res.arr[k++] = left.arr[i] + right.arr[j];
    }
    for (; i < left.len; ++i) {
        res.arr[k++] += left.arr[i];
    }
    for (; j < right.len; ++j) {
        res.arr[k++] += right.arr[j];
    }
    res.len = k;
    for (i = 0; i < k; ++i) {
        res.arr[i + 1] += res.arr[i] / 10;
        res.arr[i] %= 10;
    }
    if (res.arr[res.len]) {
        ++res.len;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const BIGINT& bigint) {
    for (int i = bigint.len - 1; i >= 0; --i) {
        os << bigint.arr[i];
    }
    return os;
}

char buf1[MAX_DIGIT], buf2[MAX_DIGIT];

int main() {
    int T;
    std::cin >> T;
    for (int i = 1; i <= T; ++i) {
        if (i > 1) { // boring, Presentation Error
            std::cout << "\n";
        }

        memset(buf1, 0, sizeof(buf1));
        memset(buf2, 0, sizeof(buf2));
        std::cin >> buf1 >> buf2;
        lhs.clear(), lhs.set(buf1);
        rhs.clear(), rhs.set(buf2);

        std::cout << "Case " << i << ":\n"
                << lhs << " + " << rhs << " = "
                << (lhs + rhs) << "\n";
    }

    return 0;
}

