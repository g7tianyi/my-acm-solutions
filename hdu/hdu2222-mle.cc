/**
 * HDU 2222 Keywords Search
 * AC-automato
 */
#include<deque>
#include<cstdio>
#include<cstring>

enum {
     MAX_ALPH = 26,
     MAX_BUFF = 50,
     MAX_NODE = 500001,
     MAX_TEXT = 1000001
};

int T; // test cases
int N; // number of words in dictionary
char buffer[MAX_BUFF];
char text[MAX_TEXT];

struct node {
public:
    node() : fail(NULL), count(0) {
        memset(next, 0, sizeof(next));
    }

public:
    node* next[MAX_ALPH];
    node* fail;
    int count; // make it a template parameter
};

node NODES[MAX_NODE];

class automata {
public:
    typedef node* node_ptr;
public:
    automata() {
        root = &NODES[0];
    }

    inline node_ptr get_root() const {
        return root;
    }

    void insert(char* word) {
        node_ptr curr = root;
        int len = strlen(word), pos, index;
        for (index = 0; index < len; ++index) {
            pos = word[index] - 'a';
            if (curr->next[pos] == NULL) {
                curr->next[pos] = get_node();
            }
            curr = curr->next[pos];
        }
        ++curr->count;
    }

    // bfs
    void adjust() {
        std::deque<node*> queue;
        queue.push_back(root);
        node_ptr curr, next;
        // for each node curr, when deal with a character ch, we trace back
        // along with its father node's fail pointer, until we found a node
        // whose child node has a valid node F corresponds to character ch,
        // then we let node curr's fail node points to F's ch child.
        // if we tracked to root and still can not find F, then node curr's
        // fail node points directly to root.
        while (!queue.empty()) {
            curr = queue.front();
            for (int i = 0; i < MAX_ALPH; ++i) {
                if (curr->next[i] != NULL) {
                    next = curr->fail;
                    while (next != NULL) {
                        if (next->next[i] != NULL) {
                            curr->next[i]->fail = next->next[i];
                            break;
                        }
                        next = next->fail;
                    }
                    if (next == NULL) {
                        curr->next[i]->fail = root;
                    }
                    queue.push_back(curr->next[i]);
                }
            }
            queue.pop_front();
        }
    }

    int find(char* str) {
        int pos, len = strlen(str), sum = 0;
        node_ptr curr = root, next;
        for (int i = 0; i < len; ++i) {
            pos = str[i] - 'a';
            while (curr != root && curr->next[pos] == NULL) {
                // backtrace, find the longest matched prefix
                curr = curr->fail;
            }
            curr = curr->next[pos];
            if (curr == NULL) {
                curr = root;
            }

            next = curr;
            while (next != root && next->count != -1) {
                // the backtracing loop deals with cases that
                // all prefix are valid words, e.g. we have,
                // { herein, here, her, he }
                sum = sum + next->count;
                next->count = -1;
                next = next->fail;
            }
        }
        return sum;
    }

private:
    inline node_ptr get_node() {
        ++SEQUENCE;
        return NODES + SEQUENCE;
    }

private:
    static int SEQUENCE;

private:
    node_ptr root;
};

int automata::SEQUENCE = 0;

int main() {

    scanf("%d", &T);

    while (T--) {
        automata ac;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            memset(buffer, 0, sizeof(buffer));
            scanf("%s", buffer);
            ac.insert(buffer);
        }
        ac.adjust();
        memset(text, 0, sizeof(text));
        scanf("%s", text);
        printf("%d\n", ac.find(text));

        memset(NODES, 0, sizeof(NODES));
    }
    
    return 0;
}

