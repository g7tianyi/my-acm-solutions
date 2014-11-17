/**
 * http://poj.org/problem?id=1658
 */
#include <iostream>

int arr[4];

enum SeqType {
    GEOMETRIC,
    ARITHMETIC
};

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        for (int i = 0; i < 4; ++i) {
            scanf("%d", &arr[i]);
            printf("%d ", arr[i]);
        }

        SeqType seqType = GEOMETRIC;
        for (int i = 2; i < 4; ++i) {
            if (arr[i - 1] - arr[i - 2] != arr[i] - arr[i - 1]) {
                seqType = GEOMETRIC;
                break;
            } else if (arr[i - 1] == 0 || arr[i - 2] == 0
                    || arr[i - 1] * arr[i - 1] != arr[i] * arr[i - 2]) {
                // don't use division here, it may lose the necessary precision
                seqType = ARITHMETIC;
                break;
            }
        }

        if (seqType == ARITHMETIC) {
            printf("%d\n", arr[3] + arr[1] - arr[0]);
        } else {
            printf("%d\n", arr[3] * arr[1] / arr[0]);
        }
    }

    return 0;
}

