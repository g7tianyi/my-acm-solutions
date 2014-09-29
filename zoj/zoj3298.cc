/**
 * ZOJ 3298, Crack
 * KMP, good KMP problem
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_BTN = 1001, MAX_SEQ = 1000001
};

int btns[MAX_BTN];
int seqs[MAX_SEQ];
int fail[MAX_BTN];

int main() {

    int N, M; // number of buttons and sequence length

    while (scanf("%d %d", &N, &M) != EOF) {
        int i, j;
        for (i = 0; i < N; ++i) {
            scanf("%d", &btns[i]);
        }
        for (j = 0; j < M; ++j) {
            scanf("%d", &seqs[j]);
        }

        // KMP: prepare fail pointers
        fail[0] = -1;
        i = 0, j = -1;
        while (i < N - 1) {
            if (j == -1 || btns[i] == btns[j]) {
                fail[++i] = ++j;
            } else {
                j = fail[j];
            }
        }

        // KMP search
        int length = 0, result = 0;
        i = 0, j = 0;
        while (i < M) { // M is the sequence length
            if (j == -1 || seqs[i] == btns[j]) {
                if (j >= 0 && seqs[i] == btns[j]) {
                    ++length;
                }
                ++i; ++j;
                if (j == N) { // N is the number of buttons
                    // printf("matching: seq[%d..%d] <=> btn[%d..%d]\n", i - N,
                    //       i - 1, j - N, j - 1);
                    // stupid requirement:
                    //  >>> peter wants to know the max number of buttons the sequence can match
                    //
                    // so, firstly, looking backward
                    int k = i - N - 1;
                    while (k >= 0 && seqs[k] == btns[(k - i + N * 2) % N]) {
                        --k; ++length;
                    }
                    // and, looking forward
                    k = i;
                    while (k < M && seqs[k] == btns[(k - i) % N]) {
                        ++k; ++length;
                    }
                    if (result < length) {
                        result = length;
                    }
                    j = 0;
                    i = i - N + 1;
                    length = 0;
                    //                   |   i
                    //           2 3 2 1 3 2 1 5
                    // matched here => 1 3 2
                    // next we should re-search from index marked with '|', i.e., i - N + 1
                }
            } else {
                j = fail[j];
                length = 0;
            }
        }

        if (result > 0) {
            printf("%d\n", result);
        } else {
            printf("bad\n");
        }
    }

    return 0;
}

