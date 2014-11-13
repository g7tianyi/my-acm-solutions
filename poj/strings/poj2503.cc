/**
 * http://poj.org/problem?id=2503
 * Hash. Open chaining.
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_WORD_LEN = 12,
    MAX_BUCKETS = 100001
};

struct HashEntry {
    char english[MAX_WORD_LEN];
    char dialect[MAX_WORD_LEN];
    HashEntry* next;
    HashEntry() :
        next(NULL) {
        memset(english, 0, sizeof(english));
        memset(dialect, 0, sizeof(dialect));
    }
    void append(HashEntry& entry) {
        if (this->dialect[0] != '\0' && this->english[0] != '\0') {
            // this hash bucket has already been occupied
            // collision resolution by chaining
            HashEntry* pEntry = new HashEntry;
            memcpy(pEntry->dialect, entry.dialect, sizeof(entry.dialect));
            memcpy(pEntry->english, entry.english, sizeof(entry.english));
            HashEntry* curr = this;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = pEntry;
        } else {
            memcpy(this->dialect, entry.dialect, sizeof(entry.dialect));
            memcpy(this->english, entry.english, sizeof(entry.english));
        }
    }
    static unsigned int hash(char* text) {
        unsigned long value = 0, temp;
        while (*text) {
            value = (value << 4) + (*text++);
            temp = value & 0xF0000000L;
            if (temp) {
                value ^= (temp >> 24);
            }
            value &= (~temp);
        }
        return static_cast<unsigned int>(value % MAX_BUCKETS);
    }
};

HashEntry entry;
HashEntry buckets[MAX_BUCKETS];
char buffer[MAX_WORD_LEN << 1];

int main() {
    unsigned int index = 0;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "%s %s", entry.english, entry.dialect) != 2) {
            break;
        }
        index = HashEntry::hash(entry.dialect);
        buckets[index].append(entry);
    }

    HashEntry* pEntry = NULL;
    while (scanf("%s", buffer) != EOF) {
        index = HashEntry::hash(buffer);
        pEntry = &buckets[index];
        while (pEntry) {
            if (!strcmp(pEntry->dialect, buffer)) {
                printf("%s\n", pEntry->english);
                break;
            }
            pEntry = pEntry->next;
        }
        if (pEntry == NULL) {
            printf("eh\n");
        }
    }

    return 0;
}

