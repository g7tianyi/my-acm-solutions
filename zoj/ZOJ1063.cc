/**
 * ZOJ 1063, Space Station Shielding
 *
 * flood-fill.
 * one common pitfall about flood fill is, your BFS/DFS will finished without traversing all node,
 * there could be chances that not all fields are connected.
 * For instance, see the input for this problem
 *  2 3 1 4
 *  0 1 2 5
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <deque>
using namespace std;

const int MAX_LEN = 61;
// length, width, height, station => m, n, k, l
int length, width, height, station;
bool require[MAX_LEN][MAX_LEN][MAX_LEN];
bool visited[MAX_LEN][MAX_LEN][MAX_LEN];

struct point {
    int x, y, z;
    point(int _x, int _y, int _z) :
            x(_x), y(_y), z(_z) {
    }
    point(int pos) {
        z = pos / (length * width);
        y = (pos % (length * width)) / length;
        x = (pos % (length * width)) % length;
    }
};

deque<point> queue;

// this floodfill function aims to find all gird that can be invaded by outer lethal bacteria
void floodfill_neutralize(int x, int y, int z) {

    queue.push_back(point(x, y, z));
    visited[x][y][z] = true;

    while (!queue.empty()) {
        point curr = queue.front();
        queue.pop_front();

        if (curr.x - 1 >= 0 && !visited[curr.x - 1][curr.y][curr.z]
                && !require[curr.x - 1][curr.y][curr.z]) {
            visited[curr.x - 1][curr.y][curr.z] = true;
            queue.push_back(point(curr.x - 1, curr.y, curr.z));
        }
        if (curr.x + 1 < length && !visited[curr.x + 1][curr.y][curr.z]
                && !require[curr.x + 1][curr.y][curr.z]) {
            visited[curr.x + 1][curr.y][curr.z] = true;
            queue.push_back(point(curr.x + 1, curr.y, curr.z));
        }
        if (curr.y - 1 >= 0 && !visited[curr.x][curr.y - 1][curr.z]
                && !require[curr.x][curr.y - 1][curr.z]) {
            visited[curr.x][curr.y - 1][curr.z] = true;
            queue.push_back(point(curr.x, curr.y - 1, curr.z));
        }
        if (curr.y + 1 < width && !visited[curr.x][curr.y + 1][curr.z]
                && !require[curr.x][curr.y + 1][curr.z]) {
            visited[curr.x][curr.y + 1][curr.z] = true;
            queue.push_back(point(curr.x, curr.y + 1, curr.z));
        }
        if (curr.z - 1 >= 0 && !visited[curr.x][curr.y][curr.z - 1]
                && !require[curr.x][curr.y][curr.z - 1]) {
            visited[curr.x][curr.y][curr.z - 1] = true;
            queue.push_back(point(curr.x, curr.y, curr.z - 1));
        }
        if (curr.z + 1 < height && !visited[curr.x][curr.y][curr.z + 1]
                && !require[curr.x][curr.y][curr.z + 1]) {
            visited[curr.x][curr.y][curr.z + 1] = true;
            queue.push_back(point(curr.x, curr.y, curr.z + 1));
        }
    }
}

// BFS
int floodfill_shield(int x, int y, int z) {
    visited[x][y][z] = true;
    queue.push_back(point(x, y, z));

    int res = 0;
    while (!queue.empty()) {
        point curr = queue.front();
        queue.pop_front();

        // flood to horizontal right
        if (curr.x == length - 1 || !require[curr.x + 1][curr.y][curr.z]) {
            ++res;
        } else if (!visited[curr.x + 1][curr.y][curr.z]) {
            visited[curr.x + 1][curr.y][curr.z] = true;
            queue.push_back(point(curr.x + 1, curr.y, curr.z));
        }

        // flood to horizontal upper
        if (curr.y == width - 1 || !require[curr.x][curr.y + 1][curr.z]) {
            ++res;
        } else if (!visited[curr.x][curr.y + 1][curr.z]) {
            visited[curr.x][curr.y + 1][curr.z] = true;
            queue.push_back(point(curr.x, curr.y + 1, curr.z));
        }

        // flood to vertical upper
        if (curr.z == height - 1 || !require[curr.x][curr.y][curr.z + 1]) {
            ++res;
        } else if (!visited[curr.x][curr.y][curr.z + 1]) {
            visited[curr.x][curr.y][curr.z + 1] = true;
            queue.push_back(point(curr.x, curr.y, curr.z + 1));
        }

        if (curr.x == 0 || !require[curr.x - 1][curr.y][curr.z]) {
            ++res;
        }
        if (curr.y == 0 || !require[curr.x][curr.y - 1][curr.z]) {
            ++res;
        }
        if (curr.z == 0 || !require[curr.x][curr.y][curr.z - 1]) {
            ++res;
        }
    }

    return res;
}

int main() {

    while (scanf("%d %d %d %d", &length, &width, &height, &station) != EOF
            && length && width && height && station) {

        // 1) input
        memset(require, 0, sizeof(require));
        int num;
        for (int i = 0; i < station; ++i) {
            scanf("%d", &num);
            point acm = point(num);
            require[acm.x][acm.y][acm.z] = true;
        }

        // 2) prepare
        // if all neighbours from six directions are ACM rooms, mark it an ACM room
        memset(visited, 0, sizeof(require));
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < height; ++k) {
                    if ((i == 0 || i == length - 1
                            || j == 0 || j == width - 1
                            || k == 0 || k == height - 1) // must start from an edge grid
                                && !require[i][j][k]      // the gird does NOT require safety
                                && !visited[i][j][k]) {   // the grid has NOT been floodfilled before
                        // flood fill, find all connected grid that doesn't require safety
                        floodfill_neutralize(i, j, k);
                    }
                }
            }
        }
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < height; ++k) {
                    if (!require[i][j][k] && !visited[i][j][k]) {
                        require[i][j][k] = true;
                    }
                }
            }
        }

        // 3) floodfill ACM rooms
        // though floodfill_shield is already O(n^3)
        // the whole time cost of the following block is still O(n^3)
        int result = 0;
        memset(visited, 0, sizeof(require));
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < height; ++k) {
                    if (require[i][j][k] && !visited[i][j][k]) {
                        result += floodfill_shield(i, j, k);
                    }
                }
            }
        }

        printf("The number of faces needing shielding is %d.\n", result);
    }

    return 0;
}

