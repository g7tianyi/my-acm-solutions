#include <iostream>

inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}

#include <vector>
#include <cstring>

using std::vector;
static int const MASK[9] = { 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
        1 << 7, 1 << 8 };

enum FlagType {
    HORIZON = 0, VERTICAL = 9, GRID = 18
};

struct Flag {
public:
    Flag() {
        memset(arr, 0, sizeof(arr));
    }
    bool mark(int index, int num, FlagType flagType) {
        index += flagType;
        if (arr[index] & MASK[num]) {
            return false;
        }
        arr[index] |= MASK[num];
        return true;
    }
private:
    int arr[30];
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char> >& board) {
        if (board.empty() || board[0].empty()) {
            return false;
        }
        Flag flag;
        // check HORIZON
        int num;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                num = board[i][j] - '1';
                if (!flag.mark(i, num, HORIZON)
                        || !flag.mark(j, num, VERTICAL)
                        || !flag.mark((i / 3) * 3 + j / 3, num, GRID)) {
                    return false;
                }
            }
        }

        return true;
    }
};
Solution sol;

int main() {
    vector<vector<char> > V;
    for (int i = 0; i < 9; ++i) {
        vector<char> C;
        for (int j = 0; j < 9; ++j) {
            C.push_back('.');
        }
        V.push_back(C);
    }

    V[0][0] = '5', V[0][1] = '3', V[0][4] = '7';
    V[1][0] = '6', V[1][3] = '1', V[1][4] = '9', V[1][5] = '5';
    V[2][1] = '9', V[2][2] = '8', V[2][7] = '6';
    V[3][0] = '8', V[3][4] = '6', V[3][8] = '3';
    V[4][0] = '4', V[4][3] = '8', V[4][5] = '3', V[4][8] = '1';
    V[5][0] = '7', V[5][4] = '2', V[5][8] = '6';
    V[6][1] = '6', V[6][6] = '2', V[6][7] = '8';
    V[7][3] = '4', V[7][4] = '1', V[7][5] = '9', V[7][8] = '5';
    V[8][4] = '8', V[8][7] = '7', V[8][8] = '9';

    if (sol.isValidSudoku(V)) {
        std::cout << "Valid Sudoku." << std::endl;
    } else {
        std::cout << "Invalid Sudoku." << std::endl;
    }

    V[7][0] = '8';
    if (sol.isValidSudoku(V)) {
        std::cout << "Valid Sudoku." << std::endl;
    } else {
        std::cout << "Invalid Sudoku." << std::endl;
    }

    return 0;
}

