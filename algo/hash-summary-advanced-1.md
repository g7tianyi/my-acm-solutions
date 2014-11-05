哈希問題的小結：平方探測哈希
====

> 致谢：  [馬大叔](http://users.cis.fiu.edu/~weiss/) 以及 [Quadratic Probing by Wikipedia](http://en.wikipedia.org/wiki/Quadratic_probing)

建議先看以上的資料再聽我這沒水準的唧唧歪歪。

##基本理解

平方探測也是一種在發生哈希衝突時候呀解決衝突的辦法，思路就是Wikipedia上的這段話以及偽代碼：

> ![enter image description here](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/quadratic_probing_1.png)

> ![enter image description here](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/quadratic_probing_2.png)

非常好懂，不必廢話。

需要啰嗦幾句的是刪除操作，任何數據結構，刪除都需要倍加小心。

删除的时候仅仅将标记为置为DELETED状态，不改变此时的__capacity，接下来，下一次再对这个key运行__find_pos或某个key冲突到这个位置时：

- 如果插入的Key就等于这个位置上原来存在的Key，直接更新该位置上的Value即可
- 如果插入的Key不等于这个位置上原来存在的Key，则此空间不能利用，需要继续往“前”运行平方探测

##編程實現
```C++
#include <functional>
#include <iterator>
#include <iostream>

#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
#  define LOG_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#  define LOG_DEBUG(fmt, ...)  do {} while (0)
#endif


namespace hash {

template<typename Key>
struct MyHasher: public std::unary_function<Key, unsigned> {
    inline unsigned operator()(const Key& key) const;
};

template<>
struct MyHasher<unsigned> {
    MyHasher(unsigned table_size) : __table_size(table_size) {}
    inline unsigned operator()(const unsigned& key) const {
        return key % __table_size;
    }
private:
    unsigned __table_size;
};

static const unsigned __min_hash_capacity = 97;

static unsigned nearest_prime(unsigned number, unsigned min_prime = __min_hash_capacity) {
    while (number > min_prime) {
        unsigned downto = number >> 1;
        bool found = true;
        for (unsigned i = 2; i <= downto; ++i) {
            if (number % i == 0) {
                found = false;
                break;
            }
        }
        if (found) {
            break;
        }
        --number;
    }
    return number;
}

template<typename Key, typename Value, typename Hasher = MyHasher<Key> >
class QuadraticHasher {
public:
    explicit QuadraticHasher(unsigned table_size = __min_hash_capacity) :
            __table_size(nearest_prime(table_size)),
            __capacity(__table_size),
            __hasher(Hasher(__table_size)) {
        __entries = new Entry[__table_size];
    }

    ~QuadraticHasher() {
        delete [] __entries;
    }

    void insert(const Key& key, const Value& value) {
        unsigned pos = __find_pos(key);
        if (pos >= __table_size) { // failed to find a legitimate hash entry
            return;
        }

        ++__capacity;
        __entries[pos].entryFlag = OCCUPIED;
        __entries[pos].key = key;
        __entries[pos].value = value;

        if (__capacity >= (__table_size >> 1)) {
            __rehash();
        }
    }

    void remove(const Key& key) {
        unsigned pos = __find_pos(key);
        if (pos >= __table_size) {
            return;
        }
        // we can not remove elements in the hash entries since it may already
        // cause collision leading the conflicted element being hashed to other
        // position. when we do searching (find), we stop when encoutering
        // 'AVAILABLE' position, makes us unable to find the element again
        //
        // in lazy-deletion, we mark the entry as 'DELETED'
        // next time we run __find_pos, the position'd be seen unavailable
        //
        // check __find_pos() to understand lazy-deletion
        if (__entries[pos].entryFlag == OCCUPIED) {
            __entries[pos].entryFlag = DELETED;
        }
    }

    bool contains(const Key& key) const {
        unsigned pos = __find_pos(key);
        return pos < __table_size && __entries[pos].entryFlag == OCCUPIED;
    }

    Value find(const Key& key) const {
        unsigned pos = __find_pos(key);
        // if __entries[pos].entryFlag is 'DELETED', hash failed
        if (pos >= __table_size || __entries[pos].entryFlag != OCCUPIED) {
            return Value(); // throw exception instead
        } else {
            return __entries[pos].value;
        }
    }

private:
    unsigned __find_pos(const Key& key) const {
        unsigned pos = __hasher(key);
        unsigned loop = 0; // avoid dead loop
        unsigned offset = 0;
        // find a pos which is either available or contains the same key
        // note a case that if __entries[pos].entryFlag is 'DELETED'
        // we check if the entry contains the same key
        // if not, we should keep finding
        while (__entries[pos].entryFlag != AVAILABLE
                && __entries[pos].key != key) {
            if (++loop == __table_size << 1) {
                return __table_size << 1; // indicating a failed hashing
            }
            // simple optimization
            // offset ^ 2 - (offset - 1) ^ 2 = offset * 2 - 1
            pos += (((++offset) << 1) - 1);
            pos %= __table_size;
        }
        return pos;
    }

    void __rehash() {
        unsigned old_size = __table_size;
        __table_size = nearest_prime(__table_size << 1, __table_size);

        LOG_DEBUG("rehash %d buckets to %d buckets", old_size, __table_size);
        Entry* old_entries = __entries;
        __entries = new Entry[__table_size];
        __capacity = 0;
        for (unsigned i = 0; i < old_size; ++i) {
            if (old_entries[i].entryFlag == OCCUPIED) {
                insert(old_entries[i].key, old_entries[i].value);
            }
        }
        delete[] old_entries;
    }

private:

    enum EntryFlag {
        AVAILABLE,
        OCCUPIED,
        DELETED,
    };

    struct Entry {
        Key       key;
        Value     value;
        EntryFlag entryFlag;
        Entry() : key(Key()), value(Value()), entryFlag(AVAILABLE) {}
    };

    unsigned __table_size;
    unsigned __capacity;
    Entry*   __entries;
    Hasher   __hasher;
};


} // end of namespace hash

#include <random>
#include <ctime>

int main() {

    hash::QuadraticHasher<unsigned, int> hasher;

    srand((unsigned) time(0));
    const int _max_key = 7919;
    int key, value;
    std::vector<int> keys;
    for (int i = 0; i < (hash::__min_hash_capacity << 1); ++i) {
        key = static_cast<unsigned>(rand() % _max_key);
        value = rand();
        std::cout << "insert " << key << " with value " << value << "\n";
        hasher.insert(key, value);
        if (rand() % 10 == 0) {
            keys.push_back(key);
        }
    }

    for (std::vector<int>::iterator pos = keys.begin();
            pos != keys.end();
            ++pos) {
        std::cout << "find " << *pos << " => " << hasher.find(*pos) << "\n";
    }

    for (int i = 0; i < 10; ++i) {
        key = static_cast<unsigned>(rand() % _max_key);
        if (hasher.contains(key)) {
            std::cout << "hasher contains " << key  << "\n";
        } else {
            std::cout << "hasher doesn't contain " << key  << "\n";
        }
    }

    return 0;
}
```
