#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using std::vector;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int size = digits.size();
        digits[size - 1] += 1;

        vector<int> V;
        for (int i = size - 1; i > 0; --i) {
            V.push_back(digits[i] % 10);
            digits[i - 1] += (digits[i] / 10);
            digits[i] %= 10;
        }
        if (digits[0] >= 10) {
            V.push_back(digits[0] % 10), V.push_back(digits[0] / 10);
        } else {
            V.push_back(digits[0]);
        }

        int i = 0, j = V.size() - 1;
        while (i < j) {
            swap(V[i++], V[j--]);
        }

        return V;
    }
private:
    inline void swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }
};
static Solution solution;

namespace stest {

static vector<int> mockRandomData(int size, int end) {
    srand((unsigned) time(0));
    vector<int> V;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 9);
    for (int i = 0, num; i < size - 1; ++i) {
        num = distribution(generator);
        if (i == 0 && num == 0) {
            num = 1;
        }
        V.push_back(num);
    }
    V.push_back(end);
    return V;
}

static vector<int> mockEdgeData(int size) {
    vector<int> V;
    for (int i = 0; i < size; ++i) {
        V.push_back(9);
    }
    return V;
}

static void test(vector<int>& V) {
    std::cout << "original number: ";
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout << std::endl;
    vector<int> C = solution.plusOne(V);
    std::cout << "plus one number: ";
    std::copy(C.begin(), C.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout << "\n" << std::endl;
}

void testRandomData() {
    vector<int> V;
    V = mockRandomData(10, 3), test(V);
    V = mockRandomData(10, 9), test(V);
    V = mockRandomData(16, 6), test(V);
    V = mockRandomData(16, 9), test(V);
    V = mockRandomData(1, 2), test(V);
    V = mockRandomData(1, 9), test(V);
    V = mockRandomData(22, 9), test(V);
    V = mockRandomData(22, 1), test(V);
    V = mockRandomData(121, 7), test(V);
    V = mockRandomData(121, 9), test(V);
}

void testEdgeData() {
    vector<int> V = mockEdgeData(121);
    test(V);
}
}

int main() {
    stest::testRandomData();
    stest::testEdgeData();
    return 0;
}

