/**
 * POJ 2752, Seek the Name, Seek the Fame
 * KMP is fascinating! the fail array has so many fantastic features.
 */
#include <deque>
#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 400005;
char text[MAX_LENGTH];
int fail[MAX_LENGTH];
std::deque<int> coll; // result collection
std::deque<int>::iterator pos;

int main() {
    while (scanf("%s", text) != EOF) {
        int textlen = strlen(text);
        // KMP: prepare fail pointers
        fail[0] = -1;
        int i = 0, j = -1;
        while (i < textlen) {
            if (j == -1 || text[i] == text[j]) {
                fail[++i] = ++j;
            } else {
                j = fail[j];
            }
        }

        coll.clear();
        coll.push_front(textlen);
        // fail pointer has one property,
        // text[0..k) == text[j-k..j)
        i = textlen;
        while (fail[i] > 0) {
            coll.push_front(fail[i]);
            i = fail[i];
        }

        for (pos = coll.begin(); pos != coll.end(); ++pos) {
            printf("%d ", *pos);
        }
        printf("\n");
    }

    return 0;
}

