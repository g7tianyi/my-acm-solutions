/**
 * POJ 1204 Word Puzzles
 * AC-automat
 */
#include<deque>
#include<vector>
#include<cstdio>
#include<cctype>
#include<cstring>

const int MAX_ALPH = 26;

int R, C, W; // row, column, words
char puzzle[1001][1001];
char buffer[10000];

struct coordinate {
    int x, y;
    coordinate() : x(0), y(0) {}
    coordinate(int _x, int _y) : x(_x), y(_y) {}
};
coordinate coordinates[1001];
char directions[1001];

struct trie_node {
    std::vector<int> tags;
    trie_node* next[MAX_ALPH];
    trie_node* failed_next;
    bool visited;
};
// tricy part to avoid dynamically allocate memory
// actually I don't like it
// maybe this is the side effect of ACM
trie_node node[100001];

class trie_ac {
public:
    trie_ac() {
        root = &node[0];
        for (int i = 0; i < MAX_ALPH; i++) {
            root->next[i] = root;
        }
        root->failed_next = root;
        root->visited = false;
    }

    trie_node* get_root() const {
        return root;
    }

    // this might be the template code for trie insertion
    void insert(char* buf, int tag) {
        trie_node* curr = root;
        int len = strlen(buf) - 1;
        for (; len >= 0; --len) {
            int index = buf[len] - 'A';
            if (curr->next[index] == root) {
                curr->next[index] = get_node();
            }
            curr = curr->next[index];
        }
        (curr->tags).push_back(tag);
    }

    // bfs
    void adjust() {
        std::deque<trie_node*> queue;
        for (int i = 0; i < MAX_ALPH; i++) {
            if (node[0].next[i] != root) {
                queue.push_back(node[0].next[i]);
            }
        }
        while (queue.size()) {
            trie_node* curr = queue.front();
            for (int i = 0; i < MAX_ALPH; i++) {
                trie_node *temp = curr->next[i];
                if (temp != root) {
                    queue.push_back(temp);
                    temp->failed_next = curr->failed_next->next[i];
                } else {
                    curr->next[i] = curr->failed_next->next[i];
                }
            }
            queue.pop_front();
        }
    }

private:
    trie_node* get_node() {
        ++node_seq;
        for (int i = 0; i < MAX_ALPH; i++) {
            node[node_seq].next[i] = root;
        }
        node[node_seq].failed_next = root;
        node[node_seq].visited = false;
        return node + node_seq;
    }

private:
    static int node_seq;

private:
    trie_node* root;
};

int trie_ac::node_seq = 0;

trie_ac tac;

void find(int start_x, int start_y, int step_x, int step_y, char dir) {
    trie_node* curr = tac.get_root();
    for (int i = start_x, j = start_y; i && i <= R && j && j <= C;
            i += step_x, j += step_y) {
        int pos = puzzle[i][j] - 'A';
        curr = curr->next[pos];
        for (trie_node* tmp = curr; tmp != tac.get_root() && !tmp->visited;
                tmp = tmp->failed_next) {
            if (!(tmp->tags).empty()) {
                tmp->visited = true;
                for (int k = 0; k < (tmp->tags).size(); k++) {
                    coordinates[(tmp->tags)[k]].x = i - 1;
                    coordinates[(tmp->tags)[k]].y = j - 1;
                    directions[(tmp->tags)[k]] = dir;
                }
            }
        }
    }
}

int main() {

    scanf("%d %d %d", &R, &C, &W);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            while (!isupper(puzzle[i][j] = getchar())) {
                ;
            }
        }
    }

    for (int i = 1; i <= W; ++i) {
        scanf("%s", buffer);
        tac.insert(buffer, i);
    }
    tac.adjust();

    for (int i = 1; i <= R; i++) {
        find(i, C,  1, -1, 'B');
        find(i, C,  0, -1, 'C');
        find(i, C, -1, -1, 'D');
        find(i, 1,  0,  1, 'G');
        find(i, 1, -1,  1, 'F');
        find(i, 1,  1,  1, 'H');
    }

    for (int i = 1; i <= C; i++) {
        find(R, i, -1, -1, 'D');
        find(R, i, -1,  0, 'E');
        find(R, i, -1,  1, 'F');
        find(1, i,  1,  0, 'A');
        find(1, i,  1, -1, 'B');
        find(1, i,  1,  1, 'H');
    }

    for (int i = 1; i <= W; i++) {
        printf("%d %d %c\n", coordinates[i].x, coordinates[i].y, directions[i]);
    }

    return 0;
}

