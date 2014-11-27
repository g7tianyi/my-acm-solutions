/**
 * http://poj.org/problem?id=2418
 * Hardwood Species
 *
 * simulate binary search tree by array~ interesting trial~
 */

#include <iostream>

class binary_search_tree {
public:
    binary_search_tree() : elemCount(0) {
        memset(left,  -1, sizeof(left));
        memset(right, -1, sizeof(right));
        memset(count,  0, sizeof(count));
        memset(names,  0, sizeof(names));
    }

public:
    void insert(char* name) {
        ++elemCount;
        insert(0, name);
    }

    void print() {
        print(0);
    }

private:
    void insert(int pos, char* name) {
        if (count[pos] == 0) {
            ++count[pos];
            strcpy(names[pos], name);
        } else {
            int comp = strcmp(names[pos], name);
            if (comp == 0) {
                ++count[pos];
            } else if (comp > 0) {
                if (left[pos] == -1) {
                    left[pos] = ++__next;
                }
                insert(left[pos], name);
            } else {
                if (right[pos] == -1) {
                    right[pos] = ++__next;
                }
                insert(right[pos], name);
            }
        }
    }

    void print(int pos) { // in-order traverse
        if (left[pos] != -1) {
            print(left[pos]);
        }
        printf("%s %.4f\n", names[pos], percent(pos));
        if (right[pos] != -1) {
            print(right[pos]);
        }
    }

    inline double percent(int pos) {
        return elemCount > 0 ? (100 * ((double) count[pos] / elemCount)) : 0;
    }

private:
    static int __next;
    enum {
        MAX_ELEMENT = 10001,
        NAME_LENGTH = 32
    };

    int  elemCount;
    int  left [MAX_ELEMENT];
    int  right[MAX_ELEMENT];
    int  count[MAX_ELEMENT];
    char names[MAX_ELEMENT][NAME_LENGTH];
};
int binary_search_tree::__next = 0;

static char* pb;
static char buf[32];
binary_search_tree mytree;

int main() {

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if ((pb = strchr(buf, '\n')) != NULL) {
            *pb = '\0';
        }
        mytree.insert(buf);
    }
    mytree.print();
    return 0;
}

