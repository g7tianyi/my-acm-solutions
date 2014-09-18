/*
 ID: fairyroad1106
 PROG: namenum
 LANG: C++
 */
#include <cstdio>
#include <cstring>

#define PROGID "namenum"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

const int MAX_LEN = 12;
const int ALPHABET = 26;
const char map[8][3] = {
    { 'A', 'B', 'C' }, // 2
    { 'D', 'E', 'F' }, // 3
    { 'G', 'H', 'I' }, // 4
    { 'J', 'K', 'L' }, // 5
    { 'M', 'N', 'O' }, // 6
    { 'P', 'R', 'S' }, // 7
    { 'T', 'U', 'V' }, // 8
    { 'W', 'X', 'Y' }  // 9
};

struct TRIE {
    bool word;
    TRIE* next[ALPHABET];

    TRIE() : word(false) {
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
        int i, j;
        for (i = 0; word[i]; ++i) {
            j = word[i] - 'A';
            if (curr->next[j] == NULL) {
                curr->next[j] = new TRIE();
            }
            curr = curr->next[j];
        }
        curr->word = true;
    }

    bool match(char* word) {
        TRIE* curr = this;
        int i, j;
        for (i = 0; word[i]; ++i) {
            j = word[i] - 'A';
            if (curr->next[j] == NULL) {
                return false;
            }
            curr = curr->next[j];
        }
        return curr->word;
    }
};
TRIE trie;

char word[MAX_LEN];
char code[MAX_LEN];
int  codelen;

bool dfs(int curr) {
    if (curr == codelen) {
        if (trie.match(word)) {
            printf("%s\n", word);
            return true;
        }
        return false;
    }
    bool result = false, tmpres;
    int index = code[curr] - '2';
    for (int i = 0; i < 3; ++i) {
        word[curr] = map[index][i];
        tmpres = dfs(curr + 1);
        result = result || tmpres;
    }
    return result;
}

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    FILE* fdict = fopen("dict.txt", "r");
    while (!feof(fdict)) {
        fscanf(fdict, "%s", word);
        trie.insert(word);
    }
    fclose(fdict);

    scanf("%s", code);
    codelen = strlen(code);
    memset(word, 0, sizeof(word));
    if(!dfs(0)) {
        printf("NONE\n");
    }

    return 0;
}

