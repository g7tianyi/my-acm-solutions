哈希問題的小結：Cuckoo哈希
====

> 致謝： [馬大叔](http://users.cis.fiu.edu/~weiss/)以及 http://en.wikipedia.org/wiki/Cuckoo_hashing

建議先看以上的資料再聽我這沒水準的唧唧歪歪。

##基本理解

Cuckoo Hash 是一種比較聰明的解決哈希衝突的辦法，(根據前一章的基礎)，其目的還是要使衝突概率減小然後儘量均勻分佈。

Cuckoo Hash 基本思想是Double Hashing，以插入為例：

1. 對key值hash，生成兩個hash key值，hash1和hash2, 如果對應的兩個位置上有一個為空，那麼直接把key插入即可。
2. 否則，任選一個位置，把key值插入，把已經在那個位置的key值踢出來。
3. 被踢出來的key值，需要重新插入，直到沒有key被踢出為止。

最好的示例就是馬大叔書中的例子了：

![cuckoo-hash-1](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/cuckoo-hash-1.png)

![cuckoo-hash-2](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/cuckoo-hash-2.png)

可以比較生動地感覺到，在rehash發生時，左邊這個桶裡面的數據不提地往右邊的桶里“跳”，要是右邊有衝突了，又往左邊跳。

值得注意的是，插入的第2、3步很有可能導致死循環，Cuckoo Hashing的建議是設置一個閾值，如果被踢出的次數超過這個閾值，停止循環（或遞歸）。然後看你是懶(比如我)還是勤快了，一般工業強度的設計里：

 - 或者重新分配更大的Hash桶，如std::vector一樣，不夠了就double現在的空間
 - 替換兩個新的Hash函數，如：馬叔叔的書中又一個接口叫HashFamily。這樣的代碼很靈活，我很喜歡~
 
```Java
public interface HashFamily<T> {
    int hash(T x, int which);
    int getNumberOfFunctions();
    void generateNewFunctions();
}
```
- 結合以上兩者，真心的。

##編程實現
```C++
/**
 * simple implementation of cuckoo hasher
 * no deletion yet, sorry
 * will provide a STL style implementation when I'm available
 *
 * @g7tianyi
 */
#include <functional>

#define CUCKOO_DEBUG_ENABLED 1

namespace cuckoo {

#if CUCKOO_DEBUG_ENABLED
#  define CUCKOO_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define CUCKOO_DEBUG(fmt, ...)  do {} while (0)
#endif

namespace cuckoo_impl {

struct cuckoo_hasher : public std::unary_function<const unsigned, unsigned> {
    inline unsigned operator()(const unsigned key) const;
};

struct cuckoo_level_one_hasher : cuckoo_hasher {
    cuckoo_level_one_hasher(unsigned bucket_size) :
        __bucket_size(bucket_size) {
    }
    inline unsigned operator()(const unsigned key) const {
        return key % __bucket_size;
    }
private:
    unsigned __bucket_size;
};

struct cuckoo_level_two_hasher : cuckoo_hasher  {
    cuckoo_level_two_hasher(unsigned bucket_size) :
        __bucket_size(bucket_size) {
    }
    inline unsigned operator()(unsigned key) {
        return (key / __bucket_size) % __bucket_size;
    }
private:
    unsigned __bucket_size;
};

enum {
    MAX_LOOP = 97,
    MIN_SIZE = 23
};

}

class CuckooHasher {
public:
    explicit CuckooHasher(unsigned size = 97) :
        __size(nearest_prime(size)),
        __level_one_hasher(cuckoo_impl::cuckoo_level_one_hasher(__size)),
        __level_two_hasher(cuckoo_impl::cuckoo_level_two_hasher(__size)) {
        __bucket1 = new unsigned[size];
        __bucket2 = new unsigned[size];
        memset(__bucket1, -1, sizeof(unsigned) * size);
        memset(__bucket2, -1, sizeof(unsigned) * size);
    }

    ~CuckooHasher() {
        if (__bucket1) {
            delete[] __bucket1;
        }
        if (__bucket2) {
            delete[] __bucket2;
        }
    }

    inline bool contains(unsigned key) {
        unsigned hash1 = __level_one_hasher(key);
        if (__bucket1 && __bucket1[hash1] == key) {
            return true;
        }
        unsigned hash2 = __level_two_hasher(key);
        if (__bucket2 && __bucket2[hash2] == key) {
            return true;
        }
        return false;
    }

    void insert(unsigned key) {
        if (contains(key)) {
            return;
        }

        unsigned hash1 = __level_one_hasher(key);
        unsigned hash2 = __level_two_hasher(key);

        if (__bucket1[hash1] == -1) {
            __bucket1[hash1] = key;
            CUCKOO_DEBUG("insert key %d into bucket1's pos %d", key, hash1);
        } else if (__bucket2[hash2] == -1) {
            __bucket2[hash2] = key;
            CUCKOO_DEBUG("key %d has collision with bucket1's %d, insert into bucket2's pos %d",
                    key, hash1, hash2);
        } else {
            if (rehash(__bucket1[hash1], cuckoo_impl::MAX_LOOP)) {
                __bucket1[hash1] = key;
                CUCKOO_DEBUG("rehash key %d to bucket1's pos %d", key, hash1);
            } else if (rehash(__bucket2[hash2], cuckoo_impl::MAX_LOOP)) {
                __bucket2[hash2] = key;
                CUCKOO_DEBUG("key %d has collision with bucket1's %d, rehash to bucket2's pos %d",
                        key, hash1, hash2);
            } else {
                // insertion error, may need to throw exception or
                // reallocate a larger space just like std::vector does
                // this is an implementation for illustration
                // don't use the coarse implementation for prod usage
                CUCKOO_DEBUG("failed to insert key %d", key);
            }
        }
    }

private:
    unsigned nearest_prime(unsigned num) {
        while (num > cuckoo_impl::MIN_SIZE) {
            unsigned downto = num >> 1;
            bool found = true;
            for (unsigned i = 2; i <= downto; ++i) {
                if (num % i == 0) {
                    found = false;
                    break;
                }
            }
            if (found) {
                break;
            }
            --num;
        }
        return num;
    }

    // TODO: try to implement rehash in the iterative style
    bool rehash(unsigned key, int depth) {
        if (depth <= 0) {
            return false;
        }

        unsigned hash1 = __level_one_hasher(key);
        unsigned hash2 = __level_two_hasher(key);

        if (key == __bucket1[hash1]) {
            if (__bucket2[hash2] == -1) {
                __bucket2[hash2] = key;
                return true;
            } else if (rehash(__bucket2[hash2], depth - 1)) {
                __bucket2[hash2] = key;
                return true;
            }
        } else if (key == __bucket2[hash2]) {
            if (__bucket1[hash1] == -1) {
                __bucket1[hash1] = key;
                return true;
            } else if (rehash(__bucket1[hash1], depth - 1)) {
                __bucket1[hash1] = key;
                return true;
            }
        }

        return false;
    }

private:
    unsigned __size;      // size of bucket
    unsigned* __bucket1;  // the bucket for level one hash
    unsigned* __bucket2;  // the bucket for level two hash
    cuckoo_impl::cuckoo_level_one_hasher __level_one_hasher;
    cuckoo_impl::cuckoo_level_two_hasher __level_two_hasher;
};

}

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

enum {
    TEST_DATA_SIZE = 47,
    MAX_NUMBER = 10000
};

int main() {
    // small bucket size for higher collision probability
    cuckoo::CuckooHasher hasher(TEST_DATA_SIZE >> 1);
    std::vector<unsigned> vec;
    srand((unsigned) time(0));
    for (unsigned i = 0, num; i < TEST_DATA_SIZE; ++i) {
        num = static_cast<unsigned>(rand() % MAX_NUMBER);
        vec.push_back(num);
        hasher.insert(num);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    std::vector<unsigned>::iterator pos;
    for (pos = vec.begin(); pos != vec.end(); ++pos) {
        bool found = hasher.contains(*pos);
        printf("find %d %s.\n", *pos, (found ? " succeeed" : " failed"));
    }

    printf("\n");
    for (unsigned i = 0, num; i < TEST_DATA_SIZE; ++i) {
        num = static_cast<unsigned>(rand() % MAX_NUMBER);
        bool found = hasher.contains(num);
        printf("find %d %s.\n", num, (found ? " succeeed" : " failed"));
    }

    return 0;
}
```
