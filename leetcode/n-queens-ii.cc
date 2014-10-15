#include <iostream>

const unsigned int MASK[32] = { 0, 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1
        << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16, 1 << 17, 1
        << 18, 1 << 19, 1 << 20, 1 << 21, 1 << 24, 1 << 25, 1 << 26, 1 << 27, 1 << 28, 1 << 29, 1
        << 30 };

struct QueenRunner {
public:
    int size, result, flag;
    QueenRunner(int size_) :
            size(size_), result(0), flag((1 << size_) - 1) {
    }
    void run() {
        run(0, 0, 0, 1);
    }
private:
    void run(int row, int diag1, int diag2, int depth) {
        if (depth > size) {
            ++result;
            return;
        }

        int option, next;
        option = flag & (row | diag1 | diag2);
        while (option != flag) {
            next = available(option);
            if (next <= size) {
                option = option | MASK[next];
                run(row | MASK[next], (diag1 | MASK[next]) << 1, (diag2 | MASK[next]) >> 1,
                        depth + 1);
            } else {
                return;
            }
        }
    }
    inline int available(int option) {
        for (int i = 1; i <= size; ++i) {
            if (!(option & MASK[i])) {
                return i;
            }
        }
        return size + 1;
    }
};

class Solution {
public:
    int totalNQueens(int n) {
        if (n <= 0) {
            return 0;
        }
        QueenRunner runner(n);
        runner.run();
        return runner.result;
    }
};

Solution solu;

int main() {
    for (int i = 0; i <= 15; ++i) {
        std::cout << "Queue " << i << " => " << solu.totalNQueens(i) << std::endl;
    }
    return 0;
}

