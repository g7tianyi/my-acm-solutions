#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

class Solution {
public:
    /**
     * I mis-understand the problem...
     */
    vector<int> plusOne(vector<int>& digits) {
        vector<int> V;
        int carry = 1, pos = digits.size() - 1;
        while (carry && pos >= 0) {
            V.push_back(digits[pos] ^ carry);
            carry &= digits[pos];
            --pos;
        }
        if (carry) {
            V.push_back(carry);
        }
        while (pos >= 0) {
            V.push_back(digits[pos]);
            --pos;
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
    for (int i = 0; i < size - 1; ++i) {
        V.push_back(std::abs(rand()) % 2);
    }
    V.push_back(end);
    return V;
}

static vector<int> mockEdgeData(int size) {
    vector<int> V;
    for (int i = 0; i < size; ++i) {
        V.push_back(1);
    }
    return V;
}

static void test(vector<int>& V) {
    std::cout << "original data: ";
    std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout << std::endl;
    vector<int> C = solution.plusOne(V);
    std::cout << "plus one data: ";
    std::copy(C.begin(), C.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout << "\n" << std::endl;
}

void testRandomData() {
    vector<int> V;
    V = mockRandomData(10, 0), test(V);
    V = mockRandomData(10, 1), test(V);
    V = mockRandomData(16, 0), test(V);
    V = mockRandomData(16, 1), test(V);
    V = mockRandomData(1,  0), test(V);
    V = mockRandomData(1,  1), test(V);
    V = mockRandomData(22, 0), test(V);
    V = mockRandomData(22, 1), test(V);
    V = mockRandomData(121, 1), test(V);
    V = mockRandomData(121, 0), test(V);
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

