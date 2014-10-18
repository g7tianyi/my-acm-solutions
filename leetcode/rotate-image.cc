#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

int transition[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

class Solution {
public:
    void rotate(vector<vector<int> >& matrix) {
        int length = matrix.size();
        if (length <= 1) {
            return;
        }

        int currlen = length, offset = 0;
        int coord[4][2];
        int cx, cy, curr; // curr x coordinate, curr y coordinate
        int nx, ny, next; // next x coordinate, next y coordinate
        while (currlen > 1) {
            coord[0][0] = coord[0][1] = offset;
            coord[1][0] = offset, coord[1][1] = currlen - 1 + offset;
            coord[2][0] = coord[2][1] = currlen - 1 + offset;
            coord[3][0] = currlen - 1 + offset, coord[3][1] = offset;

            for (int i = 0; i < currlen - 1; ++i) {
                cx = coord[0][0], cy = coord[0][1];
                curr = matrix[cx][cy];
                for (int j = 0; j < 4; ++j) {
                    nx = coord[(j + 1) % 4][0];
                    ny = coord[(j + 1) % 4][1];
                    next = matrix[nx][ny];
                    matrix[nx][ny] = curr;
                    curr = next;
                }
                for (int j = 0; j < 4; ++j) {
                    coord[j][0] += transition[j][0];
                    coord[j][1] += transition[j][1];
                }
            }

            currlen -= 2;
            ++offset;
        }
    }
};

Solution solu;

int main() {

    for (int k = 1; k <= 10; ++k) {
        vector<vector<int> > matrix;
        for (int i = 1; i <= k; ++i) {
            vector<int> v;
            for (int j = 1; j <= k; ++j) {
                v.push_back(k * (i - 1) + j);
            }
            matrix.push_back(v);
        }

        solu.rotate(matrix);
        for (int i = 0; i < k; ++i) {
            std::copy(matrix[i].begin(), matrix[i].end(),
                    std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

