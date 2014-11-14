/**
 * http://poj.org/problem?id=2945
 *
 * string. hash. binary search
 */

#include <algorithm>
#include <iostream>
#include <cstring>

typedef unsigned long long ullong;

enum {
    BUFFER_SIZE = 32,
    MAX_PEOPLE  = 20002
};

struct elem {
    ullong value;
    int    count;
};

inline bool entry_value_compare(const elem& lhs, const elem& rhs) {
    return lhs.value < rhs.value;
}

char buffer[BUFFER_SIZE];
elem bucket[MAX_PEOPLE];
int  result[MAX_PEOPLE];

inline int binary_search(ullong& value, int size) {
    int first = 0, last = size - 1, mid;
    while (first <= last) {
        mid = first + ((last - first) >> 1);
        if (bucket[mid].value == value) {
            return mid;
        }
        if (mid > first
                && bucket[mid].value > value
                && bucket[mid - 1].value < value) {
            return mid;
        }
        if (bucket[mid].value < value) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    return first;
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) != EOF && (M || N)) {
        memset(bucket, 0, sizeof(bucket));
        ullong hash;
        int pos, size = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%s", buffer);
            hash = 0;
            for (int j = 0; j < M; ++j) {
                hash <<= 2;
                if (buffer[j] == 'C') {
                    hash |= 0x1u;
                } else if (buffer[j] == 'G') {
                    hash |= 0x2u;
                } else if (buffer[j] == 'T') {
                    hash |= 0x3u;
                }
            }

            ++hash; // since we memset the bucket to be 0, we should avoid hash value to be 0
            pos = binary_search(hash, size);
            if (bucket[pos].value != hash) {
                ++size;
                memcpy(bucket + pos + 1, bucket + pos, sizeof(elem) * (size - pos));
                bucket[pos].value = hash;
                bucket[pos].count = 0;
            }
            ++bucket[pos].count;
        }

        memset(result, 0, sizeof(result));
        for (int i = 0; i < size; ++i) {
            ++result[bucket[i].count];
        }

        for (int i = 1; i <= N; ++i) {
            printf("%d\n", result[i]);
        }
    }

    return 0;
}

