/**
 * http://poj.org/problem?id=2014
 * Flow Layout
 */

#include <iostream>

int main() {
    int W; // maximum width
    while (scanf("%d", &W) != EOF && W) {
        int width = 0, height = 0; // result
        int leftw = W, maxh = 0; // left width and max height in the current line
        int currw, currh; // current weight/height
        while (scanf("%d %d", &currw, &currh) != EOF
                && currw != -1 && currh != -1) {
            if (leftw < currw) {
                width = std::max(width, W - leftw);
                height += maxh;
                leftw = W, maxh = 0;
            }
            leftw -= currw;
            maxh = std::max(maxh, currh);
        }
        width = std::max(width, W - leftw);
        height += maxh;
        printf("%d x %d\n", width, height);
    }
    return 0;
}

