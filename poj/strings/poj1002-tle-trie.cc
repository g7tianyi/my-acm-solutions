/**
 * POJ 1002, 487-3279
 * 1) hash => too much space, (4 * 10,000,000 / 1024) = 39062 KB...
 * 2) map  => TLE, >_<
 * 3) trie =>
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int NUM_DIGITS = 10;
const int NUM_ALPH = 26;
const char TABLE[NUM_ALPH] = {
    '2', '2', '2',      // A B C
    '3', '3', '3',      // D E F
    '4', '4', '4',      // G H I
    '5', '5', '5',      // J K L
    '6', '6', '6',      // M N O
    '7', '7', '7', '7', // P Q R S
    '8', '8', '8',      // T U V
    '9', '9', '9', '9'  // W X Y Z
};

int num;
char buffer[256];
char telnum[16];

struct trie {
    int count;
    trie* links[NUM_DIGITS];

    trie() : count(0) {
        for (int i = 0; i < NUM_DIGITS; ++i) {
            links[i] = NULL;
        }
    }
    ~trie() {
        for (int i = 0; i < NUM_DIGITS; ++i) {
            if (links[i]) {
                delete links[i];
                links[i] = NULL;
            }
        }
    }

    void add(char* word) {
        trie* curr_trie = this;
        int index;
        for (int i = 0; i < strlen(word); ++i) {
            if (word[i] != '-') {
                index = (word[i] - '0');
                if (curr_trie->links[index] == NULL) {
                    curr_trie->links[index] = new trie();
                }
                curr_trie = curr_trie->links[index];
            }
        }
        ++curr_trie->count;
    }

    bool run() {
        return run(this, 0);
    }

private:
    bool run(trie* dict, int depth) {
        if (depth == 7) {
            if(dict->count > 1) {
                for (int i = 0; i < 3; ++i) {
                    printf("%c", buffer[i]);
                }
                printf("-");
                for (int i = 3; i < 7; ++i) {
                    printf("%c", buffer[i]);
                }
                printf(" %d\n", dict->count);
                return true;
            }
            return false;
        }

        bool res = false;
        for (int i = 0; i < NUM_DIGITS; ++i) {
            if (!dict->links[i]) {
                continue;
            }
            buffer[depth] = (char) ('0' + i);
            if (run(dict->links[i], depth + 1)) {
                res = true;
            }
        }
        return res;
    }

};

trie dictionary;

int main() {
    scanf("%d", &num);
    memset(buffer, 0, sizeof(buffer));
    memset(telnum, 0, sizeof(telnum));
    int i, j, k;
    for (i = 0; i < num; ++i) {
        scanf("%s", buffer);
        j = 0, k = 0;
        while (buffer[j]) {
            if (buffer[j] != '-') {
                if (buffer[j] - 'A' >= 0 && buffer[j] - 'A' < 26) {
                    telnum[k++] = TABLE[buffer[j] - 'A'];
                } else {
                    telnum[k++] = buffer[j];
                }
            }
            ++j;
        }
        dictionary.add(telnum);
        memset(buffer, 0, sizeof(buffer));
        memset(telnum, 0, sizeof(telnum));
    }

    if (!dictionary.run()) {
        printf("No duplicates.\n");
    }

    return 0;
}

