/**
 * ZOJ 3298, Crack
 * KMP...
 * TLE. OK, can not be lazy here... >_<
 * The loop (**) is the lazy solution
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_BTN = 1001, MAX_SEQ = 1000001
};

int btns[MAX_BTN << 1];
int seqs[MAX_SEQ];
int fail[MAX_BTN << 1];
int buff[MAX_BTN];

int main() {

    int num_btn, num_seq;

    while (scanf("%d %d", &num_btn, &num_seq) != EOF) {
        int i, j, k;
        for (i = 0; i < num_btn; ++i) {
            scanf("%d", &btns[i]);
        }
        for (i = 0; i < num_seq; ++i) {
            scanf("%d", &seqs[i]);
        }
        memcpy(btns + num_btn, btns, sizeof(int) * num_btn);

        int res = 0;
        for (int s = 0; s < num_btn; ++s) { // (**)
            memcpy(buff, btns + s, sizeof(int) * num_btn);

            // KMP: prepare fail pointers
            fail[0] = -1;
            i = 0, j = -1;
            while (i < num_btn - 1) {
                if (j == -1 || buff[i] == buff[j]) {
                    fail[++i] = ++j;
                } else {
                    j = fail[j];
                }
            }

            // KMP search
            i = 0, j = 0, k = 0;
            while (i < num_seq) {
                if (j == -1 || seqs[i] == buff[j]) {
                    if (j >= 0 && seqs[i] == buff[j]) {
                        ++k;
                    }
                    ++i; ++j;
                    if (j == num_btn) {
                        j = 0;
                        if (res < k) {
                            res = k;
                        }
                    }
                } else {
                    j = fail[j];
                    k = 0;
                }
            }
        }

        if (res > 0) {
            printf("%d\n", res);
        } else {
            printf("bad\n");
        }
    }

    return 0;
}


