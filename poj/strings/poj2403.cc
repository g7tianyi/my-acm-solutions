/**
 * http://poj.org/problem?id=2403
 * Hay Points
 */

#include <iostream>

struct trie {
public:
    int   val;
    trie* next[26];

public:
    trie() : val(0) {
        for (int i = 0; i < 26; ++i) {
            next[i] = NULL;
        }
    }
    ~trie() {
        for (int i = 0; i < 26; ++i) {
            if (next[i]) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }
    void insert(char* word, int value) {
        trie* curr = this;
        for (int i = 0, j; word[i]; ++i) {
            j = word[i] - 'a';
            if (curr->next[j] == NULL) {
                curr->next[j] = new trie();
            }
            curr = curr->next[j];
        }
        curr->val = value;
    }
    int value(char* word) {
        trie* curr = this;
        for (int i = 0, j; word[i]; ++i) {
            j = word[i] - 'a';
            if (j < 0 || j >= 26 || curr->next[j] == NULL) {
                return 0;
            }
            curr = curr->next[j];
        }
        return curr ? curr->val : 0;
    }
};

trie mytrie;

int main() {
    int W, T; // nnumber of words and test cases
    scanf("%d %d", &W, &T);

    char word[32];
    memset(word, 0, sizeof(word));
    int value;
    for (int i = 0; i < W; ++i) {
        scanf("%s %d", word, &value);
        mytrie.insert(word, value);
    }

    value = 0;
    while (T) {
        scanf("%s", word);
        if (word[0] != '.') {
            value += mytrie.value(word);
        } else {
            printf("%d\n", value);
            value = 0;
            --T;
        }
    }

    return 0;
}

