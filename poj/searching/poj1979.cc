/**
 * http://poj.org/problem?id=1979
 * Red and Black
 *
 * Standard DFS
 */

#include <iostream>

const short next[4][2] = {
    { -1,  0 }, // up
    {  0,  1 }, // right
    {  1,  0 }, // down
    {  0, -1 }  // left
};

int  W, H, R; // width, height, result
char room[24][24];

inline bool cool(int x, int y) {
    return x >= 0 && x < H && y >= 0 && y < W && room[x][y] == '.';
}

void dfs(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        if (cool(x + next[i][0], y + next[i][1])) {
            room[x + next[i][0]][y + next[i][1]] = '#';
            dfs(x + next[i][0], y + next[i][1]);
            ++R;
        }
    }
}

int main() {
    while (scanf("%d %d", &W, &H) != EOF && (W || H)) {
        R = 1; // 1 is the start pos;
        memset(room, 0, sizeof(room));
        int posx = -1, posy = -1;
        for (int i = 0; i < H; ++i) {
            scanf("%s", room[i]);
            if (posx == -1 || posy == -1) {
                for (int j = 0; j < W; ++j) {
                    if (room[i][j] == '@') {
                        posx = i, posy = j;
                    }
                }
            }
        }
        dfs(posx, posy);
        printf("%d\n", R);
    }
    return 0;
}

