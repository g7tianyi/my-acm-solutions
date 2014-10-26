/**
 * HDU 1069, Monkey and Banana
 * http://acm.hdu.edu.cn/showproblem.php?pid=1069
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_BLOCK = 128;

struct Block {
    int x, y, z;
    Block() :
            x(0), y(0), z(0) {
    }
    Block(int _x, int _y, int _z) :
            x(_x), y(_y), z(_z) {
    }
    inline Block& operator=(const Block& other) {
        this->x = other.x, this->y = other.y, this->z = other.z;
        return *this;
    }
};
inline bool operator<(const Block& lhs, const Block& rhs) {
    return lhs.x < rhs.x && lhs.y < rhs.y;
}
inline bool operator==(const Block& lhs, const Block& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
Block dp[MAX_BLOCK];
int nBlock;

void addBlock(int x, int y, int z) {
    Block b(x, y, z);
    bool exists = false;
    for (int i = 0; i < nBlock; ++i) {
        if (dp[i] == b) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        dp[nBlock++] = b;
    }
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline bool comp(const Block& lhs, const Block& rhs) {
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    }
    if (lhs.y != rhs.y) {
        return lhs.y < rhs.y;
    }
    return lhs.z < rhs.z;
}

int main() {
    int N, x, y, z, T = 0;
    while (scanf("%d", &N) != EOF && N) {
        nBlock = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d %d %d", &x, &y, &z);
            addBlock(x, y, z), addBlock(x, z, y);
            addBlock(y, x, z), addBlock(y, z, x);
            addBlock(z, x, y), addBlock(z, y, x);
        }

        std::sort(dp, dp + nBlock, comp);
        // F(i), max height building from the first i blocks
        int result = dp[0].z, curmax;
        for (int i = 1; i < nBlock; ++i) {
            curmax = dp[i].z;
            for (int j = 0; j < i; ++j) {
                if (dp[j] < dp[i] && curmax < dp[j].z + dp[i].z) {
                    curmax = dp[j].z + dp[i].z;
                }
            }
            dp[i].z = curmax;
            result = max(result, curmax);
        }

        printf("Case %d: maximum height = %d\n", ++T, result);
    }
    return 0;
}

