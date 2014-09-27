/*
 ID:fairyroad1106
 LANG:C++
 TASK:ariprog
 */

#include <fstream>
#include <algorithm>
using namespace std;

struct point {
    int a;
    int b;
};
point pt[20000];

inline bool myComp(point p1, point p2) {
    return (p1.b < p2.b) || ((p1.b == p2.b) && (p1.a < p2.a));
}

bool flag[125001];
int bisquare[32000];

int main() {
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int n, m, len = 0, count = 0;
    fin >> n >> m;
    for (int i = 0; i <= 125000; i++)
        flag[i] = false;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= m; j++)
            flag[i * i + j * j] = true;

    m = m * m * 2;
    for (int i = 0; i <= m; i++) {
        if (flag[i]) {
            len++;
            bisquare[len] = i;
        }
    }

    for (int i = 1; i <= len; i++) {
        for (int j = i + 1; j <= len; j++) {
            if ((n - 1) * (bisquare[j] - bisquare[i]) + bisquare[i] > m) {
                break; // pruning
            }
            bool tag = true;
            for (int k = 1; k <= n - 2; k++) {
                if (!flag[bisquare[j] + (bisquare[j] - bisquare[i]) * k]) {
                    tag = false;
                    break;
                }
            }
            if (tag) {
                ++count;
                pt[count].a = bisquare[i]; // first item
                pt[count].b = bisquare[j] - bisquare[i]; // tolerance
            }
        }
    }

    sort(pt, pt + count + 1, myComp);

    if (count == 0)
        fout << "NONE" << endl;

    for (int i = 1; i <= count; i++)
        fout << pt[i].a << " " << pt[i].b << endl;

    return 0;
}

