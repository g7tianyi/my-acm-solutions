#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    string getPermutation(int n, int k) {
        string result;
        if (k <= 0) {
            return result;
        }

        vector<int> fact(n); // factorial
        vector<bool> used(n, false);
        fact[0] = 1;
        for (int i = 1; i < n; ++i) {
            fact[i] = (i + 1) * fact[i - 1];
        }
        if (k > fact[n - 1]) {
            k = fact[n - 1];
        }

        int i = n - 1, j;
        --k;
        while (i > 0) {
            j = findNum(used, k / fact[i - 1]);
            result += ('0' + j);
            k = k % fact[--i];
        }
        j = findNum(used, 0);
        result += ('0' + j);

        return result;
    }
private:
    inline int findNum(vector<bool>& used, int pos) {
        int i = 0, j = 0;
        for (; i < used.size(); ++i) {
            if (!used[i]) {
                if (j++ == pos) {
                    break;
                }
            }
        }
        used[i] = true;
        return i + 1;
    }
};

Solution solu;

int main() {
    for (int i = 1; i <= 13; ++i) {
        printf("(4, %d) => %s\n", i, solu.getPermutation(4, i).c_str());
    }
    return 0;
}

