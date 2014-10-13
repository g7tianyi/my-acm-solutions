#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::string;
using std::vector;

static int const moves[2][2] = {
    { -1, -1 }, { -1, 1 }
};

struct DFSRunner {
    int size;
    vector<vector<string> >& result;
    DFSRunner(int size_, vector<vector<string> >& result_)
        : size(size_), result(result_)
    {}

    void run(int row, vector<string>& board) {
        if (row == size) {
            vector<string> C(board);
            result.push_back(C);
            return;
        }
        for (int column = 0; column < size; ++column) {
            if (isValidForColumn(board, row, column)
                    && isValidForDiagonal(board, row, column)) {
                board[row][column] = 'Q';
                run(row + 1, board);
                board[row][column] = '.';
            }
        }
    }
private:
    inline bool isValidForColumn(vector<string>& board, int maxRow, int column) {
        for (int row = 0; row < maxRow; ++row) {
            if (board[row][column] == 'Q') {
                return false;
            }
        }
        return true;
    }
    inline bool isValidForDiagonal(vector<string>& board, int row, int column) {
        int nextRow, nextColumn;
        for (int k = 0; k < 2; ++k) {
            int i = 1;
            while (true) {
                nextRow = row + i * moves[k][0];
                nextColumn = column + i * moves[k][1];
                if (nextRow >= 0 && nextRow < size
                        && nextColumn >= 0 && nextColumn < size) {
                    if (board[nextRow][nextColumn] == 'Q') {
                        return false;
                    }
                } else {
                    break;
                }
                ++i;
            }
        }
        return true;
    }
};


class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > result;
        if (n <= 0) {
            return result;
        }
        string initial;
        for (int i = 0; i < n; ++i) {
            initial += '.';
        }
        vector<string> board;
        for (int i = 0; i < n; ++i) {
            string row(initial);
            board.push_back(row);
        }

        DFSRunner runner(n, result);
        runner.run(0, board);
        return result;
    }
};

Solution solu;

void print(int n, vector<vector<string> >& result) {
    std::cout << "Queue of " << n << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    vector<vector<string> > result;
    for (int i = 1; i <= 10; ++i) {
        result = solu.solveNQueens(i);
        print(i, result);
    }
    return 0;
}

