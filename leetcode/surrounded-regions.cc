#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
using std::vector;

const int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

class Solution {
public:
    void solve(vector<vector<char> >& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }

        int numRow = board.size(), numCol = board[0].size();

        for (int i = 0; i < numCol; ++i) {
            if (board[0][i] == 'O') {
                floodfill(0, i, board, numRow, numCol);
            }
            if (board[numRow - 1][i] == 'O') {
                floodfill(numRow - 1, i, board, numRow, numCol);
            }
        }

        for (int i = 1; i < numRow - 1; ++i) {
            if (board[i][0] == 'O') {
                floodfill(i, 0, board, numRow, numCol);
            }
            if (board[i][numCol - 1] == 'O') {
                floodfill(i, numCol - 1, board, numRow, numCol);
            }
        }

        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numCol; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
                if (board[i][j] == '#') {
                    board[i][j] = 'O';
                }
            }
        }
    }
private:
    void floodfill(int x, int y, vector<vector<char> >& board, int numRow, int numCol) {
        board[x][y] = '#';
        int nextx, nexty;
        for (int i = 0; i < 4; ++i) {
            nextx = x + dirs[i][0], nexty = y + dirs[i][1];
            if ((nextx > 0 && nextx < numRow) && (nexty > 0 && nexty < numCol) && board[nextx][nexty] == 'O') {
                floodfill(nextx, nexty, board, numRow, numCol);
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
    test(1000, 1000);
    for (int i = 3; i <= 6; ++i) {
        for (int j = 3; j <= 6; ++j) {
            test(i, j);
        }
    }
    return 0;
}

