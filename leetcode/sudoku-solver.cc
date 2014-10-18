#include <cstring>
#include <vector>
using std::vector;

static int const MASK[9] = { 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8 };

enum LocationType {
    HORIZON = 0, VERTICAL = 9, GRID = 18
};

struct Location {
    int x, y;
    Location() :
        x(0), y(0) {
    }
    Location(int x_, int y_) :
        x(x_), y(y_) {
    }
    Location(int x_, int y_, char ch_) :
        x(x_), y(y_) {
    }
};

struct Status {
public:
    Status() {
        memset(arr, 0, sizeof(arr));
    }
    inline bool valid(Location& loc, int num) {
        return !((arr[loc.x + HORIZON] & MASK[num]) || (arr[loc.y + VERTICAL] & MASK[num])
                || (arr[(loc.x / 3) * 3 + loc.y / 3 + GRID] & MASK[num]));
    }
    inline void mark(Location& loc, int num) {
        arr[loc.x + HORIZON] |= MASK[num];
        arr[loc.y + VERTICAL] |= MASK[num];
        arr[(loc.x / 3) * 3 + loc.y / 3 + GRID] |= MASK[num];
    }
    inline void unmark(Location& loc, int num) {
        arr[loc.x + HORIZON] ^= MASK[num];
        arr[loc.y + VERTICAL] ^= MASK[num];
        arr[(loc.x / 3) * 3 + loc.y / 3 + GRID] ^= MASK[num];
    }
private:
    int arr[30];
};

class Solution {
public:
    typedef vector<vector<char> > Matrix;
    void solveSudoku(Matrix& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }

        Status status;
        int num;
        vector<Location> locs;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    locs.push_back(Location(i, j));
                    continue;
                }
                num = board[i][j] - '1';
                Location loc(i, j);
                status.mark(loc, num);
            }
        }

        solveSudoku(board, status, locs, 0);
    }
private:
    bool solveSudoku(Matrix& board, Status& status, vector<Location>& locs, int curr) {
        if (curr == locs.size()) {
            return true;
        }
        for (int i = 0; i < 9; ++i) {
            Location& loc = locs[curr];
            if (status.valid(loc, i)) {
                status.mark(loc, i);
                board[loc.x][loc.y] = '1' + i;
                if (solveSudoku(board, status, locs, curr + 1)) {
                    return true;
                }
                board[loc.x][loc.y] = '.';
                status.unmark(locs[curr], i);
            }
        }
        return false;
    }
};

Solution solu;

int main() {
    vector<vector<char> > board;

    vector<char> v0(9, '.');
    v0[0] = '5', v0[1] = '3', v0[4] = '7';
    vector<char> v1(9, '.');
    v1[0] = '6', v1[3] = '1', v1[4] = '9', v1[5] = '5';
    vector<char> v2(9, '.');
    v2[1] = '9', v2[2] = '8', v2[7] = '6';

    vector<char> v3(9, '.');
    v3[0] = '8', v3[4] = '6', v3[8] = '3';
    vector<char> v4(9, '.');
    v4[0] = '4', v4[3] = '8', v4[5] = '3', v4[8] = '1';
    vector<char> v5(9, '.');
    v5[0] = '7', v5[4] = '2', v5[8] = '6';

    vector<char> v6(9, '.');
    v6[1] = '6', v6[6] = '2', v6[7] = '8';
    vector<char> v7(9, '.');
    v7[3] = '4', v7[4] = '1', v7[5] = '9', v7[8] = '5';
    vector<char> v8(9, '.');
    v8[4] = '8', v8[7] = '7', v8[8] = '9';

    board.push_back(v0), board.push_back(v1), board.push_back(v2);
    board.push_back(v3), board.push_back(v4), board.push_back(v5);
    board.push_back(v6), board.push_back(v7), board.push_back(v8);

    for (int i = 0; i < board.size(); ++i) {
        std::copy(board[i].begin(), board[i].end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }

    std::cout << std::endl;

    solu.solveSudoku(board);
    for (int i = 0; i < board.size(); ++i) {
        std::copy(board[i].begin(), board[i].end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

