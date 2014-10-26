/**
 * POJ 1056, IMMEDIATE DECODABILITY
 * Trie
 */

#include <cstdio>
#include <cstring>

enum {
    MAX_BIT = 2, MAX_LEN = 128
};

char buffer[MAX_LEN];

struct TRIE {
    typedef TRIE* pointer;

    bool word;
    pointer next[MAX_BIT];

    TRIE() : word(false) {
        for (int i = 0; i < MAX_BIT; ++i) {
            next[i] = NULL;
        }
    }

    ~TRIE() {
        for (int i = 0; i < MAX_BIT; ++i) {
            if (next[i]) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }

    bool insert(char* word) {
        bool new_word = false, meet_word = false;
        pointer curr = this;
        int i, j;
        for (i = 0; word[i]; ++i) {
            j = word[i] - '0';
            if (curr->next[j] == NULL) {
                new_word = true;
                curr->next[j] = new TRIE();
            }
            curr = curr->next[j];
            meet_word = meet_word || curr->word;
        }
        curr->word = true;
        return !meet_word && new_word;
    }

};

int main() {
    TRIE* trie = new TRIE();
    int cases = 0;
    bool result = true;
    while (scanf("%s", buffer) != EOF) {
        if (buffer[0] != '9') {
            result = result && trie->insert(buffer);
        } else {
            if (result) {
                printf("Set %d is immediately decodable\n", ++cases);
            } else {
                printf("Set %d is not immediately decodable\n", ++cases);
            }
            delete trie;
            trie = new TRIE();
            result = true;
        }
    }
    return 0;
}

