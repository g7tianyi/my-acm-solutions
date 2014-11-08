#include <iostream>
using namespace std;

int height(int n) {
    int result = 1;
    for(int i = 1; i <= n; ++i) {
        if (i & 0x1u) {
            result <<= 1;
        } else {
            result += 1;
        }
    }
    return result;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << height(n) << endl;
    }
}

