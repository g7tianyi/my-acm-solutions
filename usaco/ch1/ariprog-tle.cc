/*
 ID: fairyroad1106
 PROG: ariprog
 LANG: C++
 */
#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

#define PROGID "ariprog"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

std::set<int> squares;

struct ARITHMETIC {
    int start, scale;
    ARITHMETIC(int _start, int _scale) :
            start(_start), scale(_scale) {
    }
};
inline bool operator<(const ARITHMETIC& lhs, const ARITHMETIC& rhs) {
    if (lhs.scale != rhs.scale) {
        return lhs.scale < rhs.scale;
    }
    return lhs.start < rhs.start;
}
std::vector<ARITHMETIC> result;

int main() {
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    int sum;
    for (int i = 0; i <= M; ++i) {
        for (int j = 0; j <= M; ++j) {
            sum = i * i + j * j;
            if (std::find(squares.begin(), squares.end(), sum)
                    == squares.end()) {
                squares.insert(sum);
            }
        }
    }

    for (int i = 0; i <= M * M * 2; ++i) { // sequence start number
        for (int j = 1; i + j * (N - 1) <= M * M * 2; ++j) { // scale
            bool valid = true;
            for (int k = 0; k < N; ++k) { // check each number in the sequence
                sum = i + j * k;
                if (std::find(squares.begin(), squares.end(), sum)
                        == squares.end()) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result.push_back(ARITHMETIC(i, j));
            }
        }
    }

    if (result.empty()) {
        printf("NONE\n");
    } else {
        std::sort(result.begin(), result.end());
        for (std::vector<ARITHMETIC>::iterator pos = result.begin();
                pos != result.end(); ++pos) {
            printf("%d %d\n", pos->start, pos->scale);
        }
    }

    return 0;
}

