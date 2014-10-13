#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
using std::vector;

struct point {
    int x, y;
    point() : x(0), y(0) {}
    point(int x_, int y_) : x(x_), y(y_) {}
    inline const point operator+(const point &other) const {
        return point(this->x + other.x, this->y + other.y);
    }
};

const point dirs[4] = { point(1, 0), point(-1, 0), point(0, 1), point(0, -1) };

class Solution {
public:
    void solve(vector<vector<char> >& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }

        int numRow = board.size(), numColumn = board[0].size();
        for (int i = 0; i < numColumn; ++i) {
            if (board[0][i] == 'O') {
                point start(0, i);
                floodfill(start, board, numRow, numColumn);
            }
            if (board[numRow - 1][i] == 'O') {
                point start(numRow - 1, i);
                floodfill(start, board, numRow, numColumn);
            }
        }

        for (int i = 0; i < numRow; ++i) {
            if (board[i][0] == 'O') {
                point start(i, 0);
                floodfill(start, board, numRow, numColumn);
            }
            if (board[i][numColumn - 1] == 'O') {
                point start(i, numColumn - 1);
                floodfill(start, board, numRow, numColumn);
            }
        }

        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numColumn; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
                if (board[i][j] == 'E') {
                    board[i][j] = 'O';
                }
            }
        }
    }
private:
    void floodfill(point& start, vector<vector<char> > &board, int numRow, int numColumn) {
        std::deque<point> queue;
        queue.push_back(start);
        point curr, next;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop_front();
            board[curr.x][curr.y] = 'E';
            for (int i = 0; i < 4; ++i) {
                next = curr + dirs[i];
                if ((next.x >= 0 && next.x < numRow)
                        && (next.y >= 0 && next.y < numColumn)
                        && board[next.x][next.y] == 'O') {
                    queue.push_back(next);
                }
            }
        }
    }
};

Solution solu;

#include <ctime>
#include <unistd.h>
vector<vector<char> > matrix;

void init(int row, int column) {
    matrix.clear();
    usleep(1000 * 1000);
    srand((unsigned) time(0));
    for (int i = 0; i < row; ++i) {
        vector<char> v;
        for (int j = 0; j < column; ++j) {
            v.push_back((rand() % 4) ? 'X' : 'O');
        }
        matrix.push_back(v);
    }
}

void print() {
    for (int i = 0; i < matrix.size(); ++i) {
        std::copy(matrix[i].begin(), matrix[i].end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }
}

void test(int row, int column) {
    init(row, column);
    for (int i = 0; i < column - 1; ++i) {
        std::cout << "--";
    }
    std::cout << "-\n";
    print();
    solu.solve(matrix);
    for (int i = 0; i < column - 1; ++i) {
        std::cout << "--";
    }
    std::cout << "-\n";
    print();
    std::cout << std::endl;
}

int main() {
    for (int i = 5; i <= 10; ++i) {
        for (int j = 5; j <= 10; ++j) {
            test(i, j);
        }
    }
    return 0;
}

