/**
 * http://poj.org/problem?id=1077
 *
 * BFS
 */

#include <iostream>
#include <queue>
#include <set>

typedef unsigned long long ullong;

struct Node {
    ullong state;
    std::string path;
    Node(ullong state_) : state(state_), path("") {}
    Node(ullong state_, std::string path_) : state(state_), path(path_) {}
};

static const ullong BITS = 0xFFFFFFFFFu;
static const ullong DEST = 4886718336; // 0001 0010 0011 0100 0101 0110 0111 1000 0000
static const int    GRID = 9;
static const ullong MASK[GRID] = {
    15 <<  0, 15 <<  4, 15 <<  8,
    15 << 12, 15 << 16, 15 << 20,
    15 << 24, 15 << 28, 15 << 32
};
static const int  TRAN[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
static const std::string DIRS[4] = { "u", "r", "d", "l" };

std::queue<Node> queue;
std::set<ullong> visit;

inline int xpos(const ullong& state) {
    int pos = 0;
    while (state & MASK[pos]) {
        ++pos;
    }
    return GRID - 1 - pos;
}

int main() {
    ullong count = 0, curr = 0, bits;
    while (count < GRID) {
        char ch = getchar();
        bits = MASK[0];
        if (ch == 'x' || ch == 'X') {
            bits = 0;
        }
        if (ch >= '1' && ch <= '8') {
            bits = ch - '0';
        }
        if (bits != 0xFu) {
            curr <<= 4;
            curr |= bits;
            ++count;
        }
    }

    Node node(curr);
    queue.push(node);
    visit.insert(curr);

    ullong next, code;
    int cpos, cx, cy, npos, nx, ny;
    while (!queue.empty()) {
        node = queue.front();
        queue.pop();

        curr = node.state;
        if (curr == DEST) {
            break;
        }

        cpos = xpos(curr);
        cx = cpos / 3, cy = cpos % 3;
        for (int i = 0; i < 4; ++i) {
            nx = cx + TRAN[i][0], ny = cy + TRAN[i][1];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                npos = nx * 3 + ny;
                code = curr & MASK[GRID - 1 - npos];
                code >>= ((GRID - 1 - npos) << 2);
                next = curr & (BITS ^ MASK[GRID - 1 - cpos]);
                next = next & (BITS ^ MASK[GRID - 1 - npos]);
                next = next | (code << ((GRID - 1 - cpos) << 2));
                if (visit.find(next) == visit.end()) {
                    std::string newpath = node.path.append(DIRS[i]);
                    Node newnode(next, node.path + DIRS[i]);
                    queue.push(newnode);
                    visit.insert(next);
                }
            }
        }
    }

    if (node.state == DEST) {
        printf("%s\n", node.path.c_str());
    } else {
        printf("unsolvable\n");
    }

    return 0;
}


