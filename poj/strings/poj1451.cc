/**
 * http://poj.org/problem?id=1451
 * T9
 *
 * Trie + BFS
 */

#include <iostream>
#include <queue>

char keymap[10][5] = {
    "####", // 0
    "####", // 1
    "abc#", // 2
    "def#", // 3
    "ghi#", // 4
    "jkl#", // 5
    "mno#", // 6
    "pqrs", // 7
    "tuv#", // 8
    "wxyz", // 9
};

char word[104];
char buffer[104];
char result[101][104];

struct prefix_tree {
    int weight;
    prefix_tree* next[26];

    prefix_tree() : weight(0) {
        for (int i = 0; i < 26; ++i) {
            next[i] = NULL;
        }
    }

    ~prefix_tree() {
        for (int i = 0; i < 26; ++i) {
            if (next[i]) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }

    void insert(char* word, int weight) {
        prefix_tree* curr = this;
        int j, len = strlen(word);
        for (int i = 0; i < len; ++i) {
            j = word[i] - 'a';
            if (curr->next[j] == NULL) {
                curr->next[j] = new prefix_tree();
            }
            curr->next[j]->weight += weight;
            curr = curr->next[j];
        }
    }

    // bfs
    void search(char* riddle) {
        std::queue<element> queue;
        element curr(this);
        queue.push(curr);
        element tagelem;
        queue.push(tagelem);

        prefix_tree* pcurr;
        int wordlen = 0, maxw = -1;
        char letter, digit = riddle[wordlen];

        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            if (curr.pointer) {
                pcurr = curr.pointer;
                for (int i = 0; i < 4; ++i) {
                    letter = keymap[digit - '0'][i];
                    if (letter != '#' && pcurr->next[letter - 'a']) {
                        element elem;
                        elem.pointer = pcurr->next[letter - 'a'];
                        strcpy(elem.word, curr.word);
                        elem.word[wordlen] = letter;
                        queue.push(elem);
                        if (maxw < elem.pointer->weight) {
                            maxw = elem.pointer->weight;
                            strcpy(buffer, elem.word);
                        }
                    }
                }
            } else {
                memcpy(result + wordlen, buffer, wordlen + 1);
                memset(buffer, 0, sizeof(buffer));
                ++wordlen;
                if (riddle[wordlen]) {
                    maxw = -1;
                    digit = riddle[wordlen];
                    queue.push(tagelem);
                }
            }
        }
    }

    // for debug
    void print() {
        std::queue<element> queue;
        element curr(this);
        queue.push(curr);
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            for (int i = 0; i < 26; ++i) {
                if (curr.pointer->next[i]) {
                    printf("%s%c %d\n", curr.word, (char) ('a' + i),
                            curr.pointer->next[i]->weight);
                    element elem(curr.pointer->next[i]);
                    strcpy(elem.word, curr.word);
                    elem.word[strlen(elem.word)] = (char) ('a' + i);
                    queue.push(elem);
                }
            }
        }
    }

private:
    struct element {
        prefix_tree* pointer;
        char word[104];
        explicit element(prefix_tree* ptr = NULL) :
                pointer(ptr) {
            memset(word, 0, sizeof(word));
        }
    };
};

int main() {
    int T, W;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Scenario #%d:\n", t);

        prefix_tree ptree;
        memset(buffer, 0, sizeof(buffer));
        for (int i = 0; i < 26; ++i) {
            buffer[0] = (char) ('a' + i);
            ptree.insert(buffer, 0);
        }

        int weight;
        scanf("%d", &W);
        while (W--) {
            scanf("%s %d", buffer, &weight);
            ptree.insert(buffer, weight);
        }

        //ptree.print();

        int M, len;
        scanf("%d", &M);
        for (int m = 1; m <= M; ++m) {
            scanf("%s", word);
            len = strlen(word);
            word[len - 1] = '\0';
            memset(result, 0, sizeof(result));
            ptree.search(word);
            for (int i = 0; i < len - 1; ++i) {
                if (result[i][0]) {
                    printf("%s\n", result[i]);
                } else {
                    printf("MANUALLY\n");
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}

