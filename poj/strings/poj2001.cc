/**
 * POJ 2001, Shortest Prefixes
 * Trie
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_LENGTH = 24,
    MAX_WORDS = 1001,
    ALPHABET = 26
};

char buff[MAX_LENGTH];
char text[MAX_WORDS][MAX_LENGTH];

struct TRIE {
    bool word;
    int count;
    TRIE* next[ALPHABET];

    TRIE() : word(false), count(0) {
        for (int i = 0; i < ALPHABET; ++i) {
            next[i] = NULL;
        }
    }

    ~TRIE() {
        for (int i = 0; i < ALPHABET; ++i) {
            if (next[i]) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }

    void insert(char* word) {
        TRIE* curr = this;
        int j, len = strlen(word);
        for (int i = 0; i < len; ++i) {
            j = word[i] - 'a';
            if (curr->next[j] == NULL) {
                curr->next[j] = new TRIE();
            }
            ++curr->next[j]->count;
            curr = curr->next[j];
        }
        ++curr->count;
        curr->word = true;
    }

    void search(char* word) {
        TRIE* curr = this;
        int j, len = strlen(word);
        for (int i = 0; i < len; ++i) {
            j = word[i] - 'a';
            if (curr->next[j]->count == 1
                    || (curr->next[j]->word && i == len - 1)) {
                memset(buff, 0, sizeof(buff));
                memcpy(buff, word, i + 1);
                printf("%s %s\n", word, buff);
                break;
            }
            curr = curr->next[j];
        }
    }
};

TRIE trie;

int main() {
    int i = 0, j;
    while (scanf("%s", text[i]) != EOF) {
        trie.insert(text[i++]);
    }
    j = i;
    for (i = 0; i < j; ++i) {
        trie.search(text[i]);
    }
    return 0;
}
