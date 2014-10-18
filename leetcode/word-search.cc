#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

// UP, RIGHT, DOWN, LEFT
const int neigbour[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

class Solution {
public:
    bool exist(vector<vector<char> >& board, string word) {
        if (board.empty() || board[0].empty()) {
            return word.empty();
        }
        if (word.empty()) {
            return false;
        }

        int row = board.size(), column = board[0].size();
        visit.clear();
        for (int i = 0; i < row; ++i) {
            vector<bool> v(column, false);
            visit.push_back(v);
        }

        bool found;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (word[0] == board[i][j]) {
                    visit[i][j] = true;
                    found = exist(board, word, 1, i, j);
                    visit[i][j] = false;
                    if (found) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
private:
    vector<vector<bool> > visit;
private:
    bool exist(vector<vector<char> >& board, string& word, int pos, int x, int y) {
        if (pos == word.size()) {
            return true;
        }
        int nx, ny;
        bool found;
        for (int i = 0; i < 4; ++i) {
            nx = x + neigbour[i][0], ny = y + neigbour[i][1];
            if (nx < board.size() && nx >= 0 && ny < board[0].size() && ny >= 0
                    && board[nx][ny] == word[pos] && !visit[nx][ny]) {
                visit[nx][ny] = true;
                found = exist(board, word, pos + 1, nx, ny);
                visit[nx][ny] = false;
                if (found) {
                    return true;
                }
            }
        }
        return false;
    }
};

Solution solu;

int main() {

    /**
     * [
     *   ["ABCE"],
     *   ["SFCS"],
     *   ["ADEE"]
     * ]
     */

    vector<vector<char> > board;
    vector<char> v0, v1, v2;
    v0.push_back('A'), v0.push_back('B'), v0.push_back('C'), v0.push_back('E');
    v1.push_back('S'), v1.push_back('F'), v1.push_back('C'), v1.push_back('S');
    v2.push_back('A'), v2.push_back('D'), v2.push_back('E'), v2.push_back('E');
    board.push_back(v0), board.push_back(v1), board.push_back(v2);

    std::cout << solu.exist(board, "ABCCED") << std::endl;
    std::cout << solu.exist(board, "ABCB") << std::endl;
    std::cout << solu.exist(board, "SEE") << std::endl;

    board.clear(), v0.clear(), v1.clear(), v2.clear();
    v0.push_back('A'), v0.push_back('B'), v0.push_back('C'), v0.push_back('E');
    v1.push_back('S'), v1.push_back('F'), v1.push_back('E'), v1.push_back('S');
    v2.push_back('A'), v2.push_back('D'), v2.push_back('E'), v2.push_back('E');
    board.push_back(v0), board.push_back(v1), board.push_back(v2);
    std::cout << solu.exist(board, "ABCEFSADEESE") << std::endl;

    return 0;
}

