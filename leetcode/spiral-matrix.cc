#include <algorithm>

#include <iostream>

//#include <string>
//using std::string;

#include <vector>
using std::vector;

enum Orientation {
    RIGHT, DOWN, LEFT, UP
};

const Orientation orientationTransition[4] = { DOWN, LEFT, UP, RIGHT };
const int positionTransition[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

struct state {
    int candx, candy;
    Orientation orien;
    state() :
            candx(0), candy(0), orien(RIGHT) {
    }
    state(int candx_, int candy_, Orientation orien_) :
            candx(candx_), candy(candy_), orien(orien_) {
    }
    inline state next() {
        return state(candx + positionTransition[orien][0],
                candy + positionTransition[orien][1], orien);
    }
    inline state turn() {
        Orientation nextOri = orientationTransition[orien];
        return state(candx + positionTransition[nextOri][0],
                candy + positionTransition[nextOri][1], nextOri);
    }
    inline static bool valid(state& s, int row, int column) {
        return s.candx < row && s.candx >= 0
                && s.candy < column && s.candy >= 0;
    }
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector<int> result;
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }

        int row = matrix.size(), column = matrix[0].size();
        vector<vector<bool> > visit;
        for (int i = 0; i < row; ++i) {
            vector<bool> v(column, false);
            visit.push_back(v);
        }

        state curr(0, 0, RIGHT), next;
        while (true) {
            visit[curr.candx][curr.candy] = true;
            result.push_back(matrix[curr.candx][curr.candy]);
            next = curr.next();
            if (!state::valid(next, row, column)
                    || visit[next.candx][next.candy]) {
                next = curr.turn();
                if (!state::valid(next, row, column)
                        || visit[next.candx][next.candy]) {
                    break;
                }
            }
            curr = next;
        }
        return result;
    }
};

Solution solu;

#include <ctime>

int main() {
    vector<vector<int> > matrix;
    for (int i = 0; i < 3; ++i) {
        vector<int> v;
        for (int j = 0; j < 3; ++j) {
            v.push_back(i * 3 + j + 1);
        }
        matrix.push_back(v);
    }

    vector<int> result;
    result = solu.spiralOrder(matrix);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    matrix.clear();
    vector<int> v;
    v.push_back(1);
    matrix.push_back(v);
    result = solu.spiralOrder(matrix);
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

