#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

enum Orientation {
    RIGHT, DOWN, LEFT, UP
};

const Orientation orientationTransition[4] = { DOWN, LEFT, UP, RIGHT };
const int positionTransition[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

struct state {
    int candx, candy; // candicate x, candicate y
    Orientation orien; // orientation
    state() :
            candx(0), candy(0), orien(RIGHT) {
    }
    state(int candx_, int candy_, Orientation orien_) :
            candx(candx_), candy(candy_), orien(orien_) {
    }
    inline state next() {
        return state(candx + positionTransition[orien][0], candy + positionTransition[orien][1],
                orien);
    }
    inline state turn() {
        Orientation nextOri = orientationTransition[orien];
        return state(candx + positionTransition[nextOri][0], candy + positionTransition[nextOri][1],
                nextOri);
    }
    inline static bool valid(state& s, int row, int column) {
        return s.candx < row && s.candx >= 0 && s.candy < column && s.candy >= 0;
    }
};

class Solution {
public:
    vector<vector<int> > generateMatrix(int size) {
        vector<vector<int> > matrix;
        if (size <= 0) {
            return matrix;
        }

        vector<vector<bool> > visit;
        for (int i = 0; i < size; ++i) {
            vector<int> vi(size, 0);
            matrix.push_back(vi);
            vector<bool> vb(size, false);
            visit.push_back(vb);
        }

        int number = 1, count = size * size;
        state curr(0, 0, RIGHT), next;
        while (number <= count) {
            visit[curr.candx][curr.candy] = true;
            matrix[curr.candx][curr.candy] = number;
            ++number;
            next = curr.next();
            if (!state::valid(next, size, size) || visit[next.candx][next.candy]) {
                next = curr.turn();
            }
            curr = next;
        }
        return matrix;
    }
};

Solution solu;

vector<vector<int> > result;

void print(int size) {
    std::cout << "Matrix : " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, "\t"));
        std::cout << std::endl;
    }
}

int main() {

    for (int i = 0; i < 10; ++i) {
        result = solu.generateMatrix(i + 1);
        print(i + 1);
    }

    return 0;
}

